#include "rasp.h"



//---------------Raspberry----------------------

#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

//---------------Variables Hardware----------------------




int Izq_1_1 = 0;
int Izq_1_2 = 0;
int Der_1_1 = 0;
int Der_1_2 = 0;
int Ctr_1_1 = 0;
int Ctr_1_2 = 0;
int Ctr_1_3 = 0;
int Tip_1_1 = 0;
//Puente 2
int Izq_2_1 = 0;
int Izq_2_2 = 0;
int Der_2_1 = 0;
int Der_2_2 = 0;
int Ctr_2_1 = 0;
int Ctr_2_2 = 0;
int Ctr_2_3 = 0;
int Tip_2_1 = 0;
//Puente 3
int Izq_3_1 = 0;
int Izq_3_2 = 0;
int Der_3_1 = 0;
int Der_3_2 = 0;
int Ctr_3_1 = 0;
int Ctr_3_2 = 0;
int Ctr_3_3 = 0;
int Tip_3_1 = 0;
//
// Set up a memory regions to access GPIO
//
void setup_io()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
    {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
                   NULL,             //Any adddress in our space will do
                   BLOCK_SIZE,       //Map length
                   PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
                   MAP_SHARED,       //Shared with other processes
                   mem_fd,           //File to map
                   GPIO_BASE         //Offset to GPIO peripheral
               );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED)
    {
        printf("mmap error %d\n", (int)gpio_map);//errno also set!
        exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;


}

void set_outputRasp()
{
    int g;
    for (g=1; g<=27; g++)
    {
        INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
        OUT_GPIO(g);
    }
}

void Apagar_P1_Der()
{
    Der_1_1 = 0;
    Der_1_2 = 0;
}
void Apagar_P1_Izq()
{
    Izq_1_1 = 0;
    Izq_1_2 = 0;
}

void Apagar_P2_Der()
{
    Der_2_1 = 0;
    Der_2_2 = 0;
}
void Apagar_P2_Izq()
{
    Izq_2_1 = 0;
    Izq_2_2 = 0;
}

void Apagar_P3_Der()
{
    Der_3_1 = 0;
    Der_3_2 = 0;
}
void Apagar_P3_Izq()
{
    Izq_3_1 = 0;
    Izq_3_2 = 0;
}




void principal(int puente,int ladoIzquierdo,int posicion,int actPosicion,int centro,int posicionCentro,int actCentro,int tipoCarro)
{
    if(puente==0)
    {
        if(ladoIzquierdo==1)
        {
            if(posicion==0)
            {
                if(actPosicion==1)
                {
                    Izq_1_1 = 1;
                }
                else
                {
                    Izq_1_1 = 0;
                }
            }
            else
            {
                if(actPosicion==1)
                {
                    Izq_1_2 = 1;
                }
                else
                {
                    Izq_1_2 = 0;
                }
            }
            if(centro==1)
            {
                if(tipoCarro==1)
                {
                    Tip_1_1=1;
                }
                else if(tipoCarro==2)
                {
                    Tip_1_1=2;
                }
                else
                {
                    Tip_1_1=0;
                }
                if(posicionCentro==0)
                {
                    if(actCentro==1)
                    {
                        Ctr_1_1 = 1;
                    }
                    else
                    {
                        Ctr_1_1 = 0;
                        Tip_1_1=0;
                    }

                }
                else if(posicionCentro==1)
                {
                    if(actCentro==1)
                    {
                        Ctr_1_2 = 1;
                    }
                    else
                    {
                        Ctr_1_2 = 0;
                        Tip_1_1=0;
                    }
                }
                else
                {
                    if(actCentro==1)
                    {
                        Ctr_1_3 = 1;
                    }
                    else
                    {
                        Ctr_1_3 = 0;
                        Tip_1_1=0;
                    }
                }
            }
            else
            {
                Tip_1_1=0;
                Ctr_1_1 = 0;
                Ctr_1_2 = 0;
                Ctr_1_3 = 0;
            }
        }
        else//-----------------Lado Derecho-----------------------
        {
            if(posicion==0)
            {
                if(actPosicion==1)
                {
                    Der_1_1 = 1;
                }
                else
                {
                    Der_1_1 = 0;
                }
            }
            else
            {
                if(actPosicion==1)
                {
                    Der_1_2 = 1;
                }
                else
                {
                    Der_1_2 = 0;
                }
            }
            if(centro==1)
            {
                if(tipoCarro==1)
                {
                    Tip_1_1=1;
                }
                else if(tipoCarro==2)
                {
                    Tip_1_1=2;
                }
                else
                {
                    Tip_1_1=0;
                }
                if(posicionCentro==0)
                {
                    if(actCentro==1)
                    {
                        Ctr_1_3 = 1;
                    }
                    else
                    {
                        Ctr_1_3 = 0;
                        Tip_1_1=0;
                    }

                }
                else if(posicionCentro==1)
                {
                    if(actCentro==1)
                    {
                        Ctr_1_2 = 1;
                    }
                    else
                    {
                        Ctr_1_2 = 0;
                        Tip_1_1=0;
                    }
                }
                else
                {
                    if(actCentro==1)
                    {
                        Ctr_1_1 = 1;
                    }
                    else
                    {
                        Ctr_1_1 = 0;
                        Tip_1_1=0;
                    }
                }
            }
            else
            {
                Tip_1_1=0;
                Ctr_1_1 = 0;
                Ctr_1_2 = 0;
                Ctr_1_3 = 0;
            }
        }
    }
    else if(puente==1)
    {
        if(ladoIzquierdo==1)
        {
            if(posicion==0)
            {
                if(actPosicion==1)
                {
                    Izq_2_1 = 1;
                }
                else
                {
                    Izq_2_1 = 0;
                }
            }
            else
            {
                if(actPosicion==1)
                {
                    Izq_2_2 = 1;
                }
                else
                {
                    Izq_2_2 = 0;
                }
            }
            if(centro==1)
            {
                if(tipoCarro==1)
                {
                    Tip_2_1=1;
                }
                else if(tipoCarro==2)
                {
                    Tip_2_1=2;
                }
                else
                {
                    Tip_2_1=0;
                }
                if(posicionCentro==0)
                {
                    if(actCentro==1)
                    {
                        Ctr_2_1 = 1;
                    }
                    else
                    {
                        Ctr_2_1 = 0;
                        Tip_2_1=0;
                    }

                }
                else if(posicionCentro==1)
                {
                    if(actCentro==1)
                    {
                        Ctr_2_2 = 1;
                    }
                    else
                    {
                        Ctr_2_2 = 0;
                        Tip_2_1=0;
                    }
                }
                else
                {
                    if(actCentro==1)
                    {
                        Ctr_2_3 = 1;
                    }
                    else
                    {
                        Ctr_2_3 = 0;
                        Tip_2_1=0;
                    }
                }
            }
            else
            {
                Tip_2_1=0;
                Ctr_2_1 = 0;
                Ctr_2_2 = 0;
                Ctr_2_3 = 0;
            }
        }
        else//-----------------Lado Derecho-----------------------
        {
            if(posicion==0)
            {
                if(actPosicion==1)
                {
                    Der_2_1 = 1;
                }
                else
                {
                    Der_2_1 = 0;
                }
            }
            else
            {
                if(actPosicion==1)
                {
                    Der_2_2 = 1;
                }
                else
                {
                    Der_2_2 = 0;
                }
            }
            if(centro==1)
            {
                if(tipoCarro==1)
                {
                    Tip_2_1=1;
                }
                else if(tipoCarro==2)
                {
                    Tip_2_1=2;
                }
                else
                {
                    Tip_2_1=0;
                }
                if(posicionCentro==0)
                {
                    if(actCentro==1)
                    {
                        Ctr_2_3 = 1;
                    }
                    else
                    {
                        Ctr_2_3 = 0;
                        Tip_2_1=0;
                    }

                }
                else if(posicionCentro==1)
                {
                    if(actCentro==1)
                    {
                        Ctr_2_2 = 1;
                    }
                    else
                    {
                        Ctr_2_2 = 0;
                        Tip_2_1=0;
                    }
                }
                else
                {
                    if(actCentro==1)
                    {
                        Ctr_2_1 = 1;
                    }
                    else
                    {
                        Ctr_2_1 = 0;
                        Tip_2_1=0;
                    }
                }
            }
            else
            {
                Tip_2_1=0;
                Ctr_2_1 = 0;
                Ctr_2_2 = 0;
                Ctr_2_3 = 0;
            }
        }
    }
    else
    {
        if(ladoIzquierdo==1)
        {
            if(posicion==0)
            {
                if(actPosicion==1)
                {
                    Izq_3_1 = 1;
                }
                else
                {
                    Izq_3_1 = 0;
                }
            }
            else
            {
                if(actPosicion==1)
                {
                    Izq_3_2 = 1;
                }
                else
                {
                    Izq_3_2 = 0;
                }
            }
            if(centro==1)
            {
                if(tipoCarro==1)
                {
                    Tip_3_1=1;
                }
                else if(tipoCarro==2)
                {
                    Tip_3_1=2;
                }
                else
                {
                    Tip_3_1=0;
                }
                if(posicionCentro==0)
                {
                    if(actCentro==1)
                    {
                        Ctr_3_1 = 1;
                    }
                    else
                    {
                        Ctr_3_1 = 0;
                        Tip_3_1=0;
                    }

                }
                else if(posicionCentro==1)
                {
                    if(actCentro==1)
                    {
                        Ctr_3_2 = 1;
                    }
                    else
                    {
                        Ctr_3_2 = 0;
                        Tip_3_1=0;
                    }
                }
                else
                {
                    if(actCentro==1)
                    {
                        Ctr_3_3 = 1;
                    }
                    else
                    {
                        Ctr_3_3 = 0;
                        Tip_3_1=0;
                    }
                }
            }
            else
            {
                Tip_3_1=0;
                Ctr_3_1 = 0;
                Ctr_3_2 = 0;
                Ctr_3_3 = 0;
            }
        }
        else//-----------------Lado Derecho-----------------------
        {
            if(posicion==0)
            {
                if(actPosicion==1)
                {
                    Der_3_1 = 1;
                }
                else
                {
                    Der_3_1 = 0;
                }
            }
            else
            {
                if(actPosicion==1)
                {
                    Der_3_2 = 1;
                }
                else
                {
                    Der_3_2 = 0;
                }
            }
            if(centro==1)
            {
                if(tipoCarro==1)
                {
                    Tip_3_1=1;
                }
                else if(tipoCarro==2)
                {
                    Tip_3_1=2;
                }
                else
                {
                    Tip_3_1=0;
                }
                if(posicionCentro==0)
                {
                    if(actCentro==1)
                    {
                        Ctr_3_3 = 1;
                    }
                    else
                    {
                        Ctr_3_3 = 0;
                        Tip_3_1=0;
                    }

                }
                else if(posicionCentro==1)
                {
                    if(actCentro==1)
                    {
                        Ctr_3_2 = 1;
                    }
                    else
                    {
                        Ctr_3_2 = 0;
                        Tip_3_1=0;
                    }
                }
                else
                {
                    if(actCentro==1)
                    {
                        Ctr_3_1 = 1;
                    }
                    else
                    {
                        Ctr_3_1 = 0;
                        Tip_3_1=0;
                    }
                }
            }
            else
            {
                Tip_3_1=0;
                Ctr_3_1 = 0;
                Ctr_3_2 = 0;
                Ctr_3_3 = 0;
            }
        }
    }
}

void *Estado_P1(void *arg)
{
    int rep;
    while(1)
    {
        if(Izq_1_1==1)
        {
            GPIO_SET = 1<<2;
        }
        else
        {
            GPIO_CLR = 1<<2;
        }
        if(Izq_1_2==1)
        {
            GPIO_SET = 1<<3;
        }
        else
        {
            GPIO_CLR = 1<<3;
        }
        if(Der_1_1==1)
        {
            GPIO_SET = 1<<4;
        }
        else
        {
            GPIO_CLR = 1<<4;
        }
        if(Der_1_2==1)
        {
            GPIO_SET = 1<<5;
        }
        else
        {
            GPIO_CLR = 1<<5;
        }
        if(Ctr_1_1==1)
        {
            GPIO_SET = 1<<6;
        }
        else
        {
            GPIO_CLR = 1<<6;
        }
        if(Ctr_1_2==1)
        {
            GPIO_SET = 1<<7;
        }
        else
        {
            GPIO_CLR = 1<<7;
        }
        if(Ctr_1_3==1)
        {
            GPIO_SET = 1<<8;
        }
        else
        {
            GPIO_CLR = 1<<8;
        }
        if(Tip_1_1==0)
        {
            GPIO_CLR = 1<<9;
        }
        else
        {
            if(Tip_1_1==1)
            {
                GPIO_SET = 1<<9;
            }
            else
            {
                GPIO_SET = 1<<9;
                /*for (rep=0; rep<2; rep++)
                {
                    GPIO_SET = 1<<9;
                    sleep(0.001);
                    GPIO_CLR = 1<<9;
                    sleep(0.001);
                }
                rep=0;*/
            }
        }

    }
    return  NULL;
}



void *Estado_P2(void *arg)
{
    int rep;
    while(1)
    {
        if(Izq_2_1==1)
        {
            GPIO_SET = 1<<10;
        }
        else
        {
            GPIO_CLR = 1<<10;
        }
        if(Izq_2_2==1)
        {
            GPIO_SET = 1<<11;
        }
        else
        {
            GPIO_CLR = 1<<11;
        }
        if(Der_2_1==1)
        {
            GPIO_SET = 1<<12;
        }
        else
        {
            GPIO_CLR = 1<<12;
        }
        if(Der_2_2==1)
        {
            GPIO_SET = 1<<13;
        }
        else
        {
            GPIO_CLR = 1<<13;
        }
        if(Ctr_2_1==1)
        {
            GPIO_SET = 1<<16;
        }
        else
        {
            GPIO_CLR = 1<<16;
        }
        if(Ctr_2_2==1)
        {
            GPIO_SET = 1<<17;
        }
        else
        {
            GPIO_CLR = 1<<17;
        }
        if(Ctr_2_3==1)
        {
            GPIO_SET = 1<<18;
        }
        else
        {
            GPIO_CLR = 1<<18;
        }
        if(Tip_2_1==0)
        {
            GPIO_CLR = 1<<19;
        }else{
            if(Tip_2_1==1)
            {
                GPIO_SET = 1<<19;
            }
            else
            {
                GPIO_SET = 1<<19;
                /*for (rep=0; rep<2; rep++)
                {
                    GPIO_SET = 1<<19;
                    sleep(0.001);
                    GPIO_CLR = 1<<19;
                    sleep(0.001);
                }
                rep=0;*/
            }
        }

    }
    return  NULL;
}

void *Estado_P3(void *arg)
{
    int rep;
    while(1)
    {
        if(Izq_3_1==1)
        {
            GPIO_SET = 1<<20;
        }
        else
        {
            GPIO_CLR = 1<<20;
        }
        if(Izq_3_2==1)
        {
            GPIO_SET = 1<<21;
        }
        else
        {
            GPIO_CLR = 1<<21;
        }
        if(Der_3_1==1)
        {
            GPIO_SET = 1<<22;
        }
        else
        {
            GPIO_CLR = 1<<22;
        }
        if(Der_3_2==1)
        {
            GPIO_SET = 1<<23;
        }
        else
        {
            GPIO_CLR = 1<<23;
        }
        if(Ctr_3_1==1)
        {
            GPIO_SET = 1<<24;
        }
        else
        {
            GPIO_CLR = 1<<24;
        }
        if(Ctr_3_2==1)
        {
            GPIO_SET = 1<<25;
        }
        else
        {
            GPIO_CLR = 1<<25;
        }
        if(Ctr_3_3==1)
        {
            GPIO_SET = 1<<26;
        }
        else
        {
            GPIO_CLR = 1<<26;
        }
        if(Tip_3_1==0)
        {
            GPIO_CLR = 1<<27;
        }else{
            if(Tip_3_1==1)
            {
                GPIO_SET = 1<<27;
            }
            else
            {
                GPIO_SET = 1<<27;
                /*for (rep=0; rep<2; rep++)
                {
                    GPIO_SET = 1<<27;
                    sleep(0.001);
                    GPIO_CLR = 1<<27;
                    sleep(0.001);
                }
                rep=0;*/
            }
        }
    }
    return  NULL;
}



