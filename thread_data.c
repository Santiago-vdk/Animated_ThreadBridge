#include <stdlib.h>
#include <stdio.h>
#include "thread_data.h"

/* Adds a new thread to the thread list */
void add_node(Thread_Carro_Puente node, ThreadList list)
{
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Thread_Carro_Puente tmp = list->head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
}

Thread_Carro_Puente get_node(ThreadList list, int thread_id)
{

    if (list->head->thread_id == thread_id)
    {
        return list-> head;
    }
    else
    {
        Thread_Carro_Puente tmp = list->head;
        while (tmp->thread_id != thread_id)
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

/* Prints the list */
void print_list(ThreadList list)
{
    if (list->head == NULL)
    {
        printf("Thread list is empty\n");
    }
    else
    {
        Thread_Carro_Puente tmp = list->head;
        while (tmp != NULL)
        {
            printf("ID: %ld\n", tmp->thread_id);
            printf("Scheduler: %d\n", tmp->calendarizador);
            printf("Type: %d\n", tmp->tipo);
            tmp = tmp->next;
        }
    }
}

/* Removes a thread node from the list */
void remove_node(int id, ThreadList list)
{
    if (list->head == NULL)
    {
        printf("Thread list is empty\n");
    }
    else
    {
        Thread_Carro_Puente tmp = list->head;
        if (tmp->thread_id == id)
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
                if (tmp->next->thread_id == id)
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
            //printf("Thread not in list\n");
        }
    }
}

/* Free the memory allocated for each node of the list */
void free_mem(ThreadList list)
{
    if (list->head == NULL)
    {
        printf("List is empty\n");
    }
    else
    {
        Thread_Carro_Puente tmp = list->head;
        while (tmp != NULL)
        {
            Thread_Carro_Puente tmp2 = tmp;
            tmp = tmp->next;
            free(tmp2);
        }
        free(tmp);
    }
}

/* Copies a node to a new node */
void copy_node(Thread_Carro_Puente src, Thread_Carro_Puente dst)
{
    dst->thread_id = src->thread_id;
    dst->calendarizador = src->calendarizador;
    dst->tipo = src->tipo;
    dst->puente = src->puente;
    dst->next = NULL;
}
