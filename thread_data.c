#include <stdlib.h>
#include <stdio.h>
#include "thread_data.h"


void agregar_puente(Thread_Puente node, ThreadListPuente list)
{
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Thread_Puente tmp = list->head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    list->tamanio = list->tamanio + 1;
}

void agregar_carro(Thread_Carro node, ThreadListCarro list)
{
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Thread_Carro tmp = list->head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    list->tamanio = list->tamanio + 1;
}


void agregar_thread(Thread node, ThreadList list)
{

    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Thread tmp = list->head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    list->tamanio = list->tamanio + 1;

}


Thread buscar_nodo_thread_carro(ThreadList list, long thread_identificador)
{
    if (list->head->carro->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread tmp = list->head;
        while (tmp->carro->thread_identificador != thread_identificador)
        {

            tmp = tmp->next;
            if (!tmp)
            {
                return NULL;
            }
        }
        return tmp;
    }
}



Thread buscar_nodo_thread_puente(ThreadList list, long thread_identificador)
{
    if (list->head->puente->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread tmp = list->head;
        while (tmp->puente->thread_identificador != thread_identificador)
        {

            tmp = tmp->next;
            if (!tmp)
            {
                return NULL;
            }
        }
        return tmp;
    }
}



Thread_Carro buscar_nodo_carro(ThreadListCarro list, long thread_identificador)
{
    if (list->head->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread_Carro tmp = list->head;
        while (tmp->thread_identificador != thread_identificador)
        {

            tmp = tmp->next;
            if (!tmp)
            {
                return NULL;
            }
        }
        return tmp;
    }
}



/* Removes a thread node from the list */
void eliminar_nodo_carro(ThreadListCarro list, long thread_identificador)
{
	if (list->head == NULL)
	{
		printf("Thread list carro is empty\n");
	}
	else
	{
		Thread_Carro tmp = list->head;
		if (tmp->thread_identificador == thread_identificador)
		{
			if (tmp->next == NULL)
			{
				list->head = NULL;
			}
			else
			{
				list->head = tmp->next;
			}
		}
		else if (tmp->next != NULL)
		{
			while (tmp->next != NULL)
			{
				if (tmp->next->thread_identificador == thread_identificador)
				{
					if (tmp->next->next != NULL)
					{
						tmp->next = tmp->next->next;
						break;
					}
					else
					{
						tmp->next = NULL;
						break;
					}
				}
				tmp = tmp->next;
			}
		}
	}
}

