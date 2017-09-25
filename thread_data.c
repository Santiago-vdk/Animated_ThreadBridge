#include <stdlib.h>
#include <stdio.h>
#include "thread_data.h"

void agregar_puente(Thread_Puente node, ThreadListPuente list)
{
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        Thread tmp = list->tail;
        list->tail = node;
        tmp->next = list->tail;
        list->tamanio += 1;
    }
}



void agregar_carro(Thread_Carro node, ThreadListCarro list)
{
    node->prev = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->tamanio += 1;
    }
}



void agregar_thread(Thread node, ThreadList list)
{

    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->tamanio += 1;
    }

}

Thread_Carro pop_primer_thread_carro(ThreadListCarro list)
{
    if (list->head != NULL)
    {
        Thread_Carro tmp = list->head;

        if(tmp->next == NULL)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio -= 1;

        }
        else
        {
            tmp->next->prev = NULL;
            list->head = tmp->next;
            tmp->next = NULL;
            list->tamanio -= 1;

        }
        return tmp;

    }
    else
    {
        printf("Lista vacia\n");
        return NULL;
    }

}

Thread pop_primer_thread(ThreadList list){
   if (list->head != NULL)
    {
        Thread tmp = list->head;

        if(tmp->next == NULL)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio -= 1;

        }
        else
        {
            tmp->next->prev = NULL;
            list->head = tmp->next;
            tmp->next = NULL;
            list->tamanio -= 1;

        }
        return tmp;

    }
    else
    {
        printf("Lista vacia\n");
        return NULL;
    }

}


Thread buscar_nodo_thread(ThreadList list, long thread_identificador)
{
    if (list->head->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread tmp = list->head;
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
void eliminar_nodo_thread(ThreadList list, long thread_identificador)
{
    if (list->head == NULL)
    {
        printf("Thread list carro is empty\n");
    }
    else
    {
        Thread tmp = list->head;

        if(list->head == list->tail && tmp->thread_identificador == thread_identificador)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio-=1;
        }
        else
        {

            if (tmp->thread_identificador == thread_identificador)
            {
                list->head = tmp->next;     // La cabeza va a ser el siguiente
                if(list->head != NULL)
                {
                    list->head->prev = NULL;
                }
                free(tmp);
                list->tamanio-=1;
            }
            else
            {
                while (tmp->next != NULL)
                {
                    if (tmp->next->thread_identificador == thread_identificador)
                    {
                        Thread tmp2 = tmp->next;
                        if (tmp->next->next != NULL)
                        {
                            tmp->next = tmp->next->next;
                            tmp->next->prev = tmp;
                            list->tamanio-=1;
                            free(tmp2);
                            break;
                        }
                        else //eliminar tail
                        {

                            tmp->next = NULL;
                            list->tail=tmp;
                            list->tamanio-=1;
                            free(tmp2);
                            break;
                        }
                    }
                    tmp = tmp->next;
                }
            }
        }
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

        if(list->head == list->tail && tmp->thread_identificador == thread_identificador)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio-=1;
        }
        else
        {
            if (tmp->thread_identificador == thread_identificador)
            {
                list->head = tmp->next;     // La cabeza va a ser el siguiente
                if(list->head != NULL)
                {
                    list->head->prev = NULL;
                }
                free(tmp);
                list->tamanio-=1;
            }
            else
            {
                while (tmp->next != NULL)
                {
                    if (tmp->next->thread_identificador == thread_identificador)
                    {
                        Thread_Carro tmp2 = tmp->next;
                        if (tmp->next->next != NULL)
                        {
                            tmp->next = tmp->next->next;
                            tmp->next->prev = tmp;
                            list->tamanio-=1;
                            free(tmp2);
                            break;
                        }
                        else //eliminar tail
                        {
                            tmp->next = NULL;
                            list->tail=tmp;
                            list->tamanio-=1;
                            free(tmp2);
                            break;
                        }
                    }
                    tmp = tmp->next;
                }
            }
        }
    }
}

