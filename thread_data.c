#include <stdlib.h>
#include <stdio.h>
#include "thread_data.h"

/* Adds a new thread to the thread list */
void add_node(TCB node, ThreadList list)
{
	if (list->head == NULL)
	{
		list->head = node;
	}
	else
	{
		TCB tmp = list->head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
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
		TCB tmp = list->head;
		while (tmp != NULL)
		{
			printf("ID: %ld\n", tmp->thread_id);
			printf("Scheduler: %d\n", tmp->scheduler);
			printf("Type: %d\n", tmp->type);
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
		TCB tmp = list->head;
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
		TCB tmp = list->head;
		while (tmp != NULL)
		{
			TCB tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
		free(tmp);
	}
}

/* Copies a node to a new node */
void copy_node(TCB src, TCB dst)
{
	dst->thread_id = src->thread_id;
	dst->scheduler = src->scheduler;
	dst->type = src->type;
	dst->bridge = src->bridge;
	dst->next = NULL;
}
