#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// insert as (100) -- (1->0->0->NULL)
int insert_at_first_DLL(DLL **head, DLL **tail, int num)
{
    DLL *new = malloc(sizeof(DLL));

    if (new == NULL)
        return FAILURE;

    new->data = num;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    new->next = *head;
    (*head)->prev = new;
    *head = new;
    return SUCCESS;
}

// insert as (10) -> 1->0->1->NULL
int insert_at_last_DLL(DLL **head, DLL **tail, int num)
{
    DLL *new = malloc(sizeof(DLL));

    if (new == NULL)
        return FAILURE;

    new->data = num;
    new->next = NULL;
    new->prev = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;

    return SUCCESS;
}

int free_DLL(DLL **head, DLL **tail)
{
    DLL *temp = *head; // first temp at head
    DLL *nextNode;     // create nextnode

    while (temp != NULL)
    {
        nextNode = temp->next; // move next node to temp of next
        free(temp);            // free the present temp
        temp = nextNode;       // now temp is the next node
    }

    // At the end when nodes are free, make head and tail as NULL
    *head = NULL;
    *tail = NULL;
}

int compare_DLL(DLL **head1, DLL **head2)
{

    DLL *temp1 = *head1;
    DLL *temp2 = *head2;

    int len1 = 0, len2 = 0;

    // find lengths
    while (temp1)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    // compare lengths
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    // lengths equal → compare digit by digit from head (MSB)
    temp1 = *head1;
    temp2 = *head2;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;
        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0; // both are equal
}

// To swap two list by changing head and tail
int swap_DLL(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2)
{
    DLL *temp_head = *head1; // take temporary head
    DLL *temp_tail = *tail1; // take temporary tail

    *head1 = *head2;
    *tail1 = *tail2;

    *head2 = temp_head;
    *tail2 = temp_tail;

    return SUCCESS;
}

// delete at first as 101 (0->1->NULL)
int delete_at_first_DLL(DLL **head, DLL **tail)
{
    if (*head == NULL) // list empty
        return 0;

    DLL *temp = *head; // initially head as temp

    // case 1: only one node
    if (*head == *tail)
    {
        *head = *tail = NULL;
        free(temp);
        return 0;
    }

    // case 2: more than one node
    *head = temp->next;
    (*head)->prev = NULL;
    free(temp);

    return 0;
}
