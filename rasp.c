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
    for (g=1; g<=26; g++)
    {
        INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
        OUT_GPIO(g);
    }
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
                    }
                }
            }
            else
            {
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
                    }
                }
            }
            else
            {
                Ctr_1_1 = 0;
                Ctr_1_2 = 0;
                Ctr_1_3 = 0;
            }
        }
    }
    else
    {
        printf("Aqui van los otrs puentes\n");
    }
}

void *Estado_P1(void *arg)
{
    int rep = 0;
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

        if(Tip_1_1)
        {
            if(Tip_1_1==1)
            {
                GPIO_SET = 1<<9;
            }
            else
            {
                //    for (rep=0; rep<3; rep++)
                //{
                //GPIO_SET = 1<<9;
                //  usleep(100000);
                //  GPIO_CLR = 1<<9;
                //   usleep(100000);
                // }
                // rep=0;
            }
        }
        else
        {
            GPIO_CLR = 1<<9;
        }
    }
    return  NULL;
}


