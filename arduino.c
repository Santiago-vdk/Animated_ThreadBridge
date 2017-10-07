#include "arduino.h"
#include "firmata.h"



t_firmata *firmata;



int Sem_Der_P1 = 0;
int Sem_Izq_P1 = 0;
int Sem_Der_P2 = 0;
int Sem_Izq_P2 = 0;
int Sem_Der_P3 = 0;
int Sem_Izq_P3 = 0;

void setup_arduino(){

    firmata = firmata_new("/dev/ttyACM0"); //init Firmata
    while(!firmata->isReady) //Wait until device is up
        firmata_pull(firmata);

    firmata_pinMode(firmata, 2, MODE_OUTPUT); // Led rojo Puente 1 Derecho
    firmata_pinMode(firmata, 3, MODE_OUTPUT); // Led verde Puente 1 Derecho
    firmata_pinMode(firmata, 4, MODE_OUTPUT); // Led rojo Puente 1 Izquierdo
    firmata_pinMode(firmata, 5, MODE_OUTPUT); // Led verde Puente 1 Izquierdo

    firmata_pinMode(firmata, 6, MODE_OUTPUT); // Led rojo Puente 2 Derecho
    firmata_pinMode(firmata, 7, MODE_OUTPUT); // Led verde Puente 2 Derecho
    firmata_pinMode(firmata, 8, MODE_OUTPUT); // Led rojo Puente 2 Izquierdo
    firmata_pinMode(firmata, 9, MODE_OUTPUT); // Led verde Puente 2 Izquierdo

    firmata_pinMode(firmata, 10, MODE_OUTPUT); // Led rojo Puente 3 Derecho
    firmata_pinMode(firmata, 11, MODE_OUTPUT); // Led verde Puente 3 Derecho
    firmata_pinMode(firmata, 12, MODE_OUTPUT); // Led rojo Puente 3 Izquierdo
    firmata_pinMode(firmata, 13, MODE_OUTPUT); // Led verde Puente 3 Izquierdo

}


void semaforo(int puente, int ladoIzquierdo, int cambio)
{
    if(puente == 0 && ladoIzquierdo == 0 && cambio == 0)
    {
        Sem_Der_P1 = 0;
    }
    else if(puente == 0 && ladoIzquierdo == 0 && cambio == 1)
    {
        Sem_Der_P1 = 1;
    }
    else if(puente == 0 && ladoIzquierdo == 1 && cambio == 0)
    {
        Sem_Izq_P1 = 0;
    }
    else if(puente == 0 && ladoIzquierdo == 1 && cambio == 1)
    {
        Sem_Izq_P1 = 1;
    }//-----------Puente 2------------------
    else if(puente == 1 && ladoIzquierdo == 0 && cambio == 0)
    {
        Sem_Der_P2 = 0;
    }
    else if(puente == 1 && ladoIzquierdo == 0 && cambio == 1)
    {
        Sem_Der_P2 = 1;
    }
    else if(puente == 1 && ladoIzquierdo == 1 && cambio == 0)
    {
        Sem_Izq_P2 = 0;
    }
    else if(puente == 1 && ladoIzquierdo == 1 && cambio == 1)
    {
        Sem_Izq_P2 = 1;
    }//-----------Puente 3------------------
    else if(puente == 2 && ladoIzquierdo == 0 && cambio == 0)
    {
        Sem_Der_P3 = 0;
    }
    else if(puente == 2 && ladoIzquierdo == 0 && cambio == 1)
    {
        Sem_Der_P3 = 1;
    }
    else if(puente == 2 && ladoIzquierdo == 1 && cambio == 0)
    {
        Sem_Izq_P3 = 0;
    }
    else if(puente == 2 && ladoIzquierdo == 1 && cambio == 1)
    {
        Sem_Izq_P3 = 1;
    }
    else
    {
        Sem_Der_P1 = 0;
        Sem_Izq_P1 = 0;
        Sem_Der_P2 = 0;
        Sem_Izq_P2 = 0;
        Sem_Der_P3 = 0;
        Sem_Izq_P3 = 0;
    }

}

void *Estado_Semaforo_P1(void *arg)
{
    while(1)
    {
        if(Sem_Der_P1==0)
        {
            firmata_digitalWrite(firmata, 2, HIGH);
            firmata_digitalWrite(firmata, 3, LOW);
        }
        else
        {
            firmata_digitalWrite(firmata, 2, LOW);
            firmata_digitalWrite(firmata, 3, HIGH);
        }
        if(Sem_Izq_P1==0)
        {
            firmata_digitalWrite(firmata, 4, HIGH);
            firmata_digitalWrite(firmata, 5, LOW);
        }
        else
        {
            firmata_digitalWrite(firmata, 4, LOW);
            firmata_digitalWrite(firmata, 5, HIGH);
        }
        usleep(10000);
    }
}
void *Estado_Semaforo_P2(void *arg)
{
    while(1)
    {
        if(Sem_Der_P2==0)
        {
            firmata_digitalWrite(firmata, 6, HIGH);
            firmata_digitalWrite(firmata, 7, LOW);
        }
        else
        {
            firmata_digitalWrite(firmata, 6, LOW);
            firmata_digitalWrite(firmata, 7, HIGH);
        }
        if(Sem_Izq_P2==0)
        {
            firmata_digitalWrite(firmata, 8, HIGH);
            firmata_digitalWrite(firmata, 9, LOW);
        }
        else
        {
            firmata_digitalWrite(firmata, 8, LOW);
            firmata_digitalWrite(firmata, 9, HIGH);
        }
        usleep(10000);
    }
}
void *Estado_Semaforo_P3(void *arg)
{
    while(1)
    {
        if(Sem_Der_P3==0)
        {
            firmata_digitalWrite(firmata, 10, HIGH);
            firmata_digitalWrite(firmata, 11, LOW);
        }
        else
        {
            firmata_digitalWrite(firmata, 10, LOW);
            firmata_digitalWrite(firmata, 11, HIGH);
        }
        if(Sem_Izq_P3==0)
        {
            firmata_digitalWrite(firmata, 12, HIGH);
            firmata_digitalWrite(firmata, 13, LOW);
        }
        else
        {
            firmata_digitalWrite(firmata, 12, LOW);
            firmata_digitalWrite(firmata, 13, HIGH);
        }
        usleep(10000);
    }
}
