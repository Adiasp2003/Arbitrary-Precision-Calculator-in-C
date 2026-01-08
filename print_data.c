#include <stdio.h>
#include <stdlib.h>
#include "head.h"

void print_data_DLL(DLL *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (head->next != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("%d\n", head->data);
}