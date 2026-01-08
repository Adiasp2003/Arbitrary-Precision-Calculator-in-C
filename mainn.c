#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        error_arguments();
        return FAILURE;
    }
    // command line arguments stored in named variable
    char *num1 = argv[1];     // first number
    char *operator = argv[2]; // operator
    char *num2 = argv[3];     // second number

    // detect negative

    int neg1 = 0, neg2 = 0;

    if (num1[0] == '-')
    {
        neg1 = 1;
        num1++; // skip '-'
    }
    if (num2[0] == '-')
    {
        neg2 = 1;
        num2++; // skip '-'
    }

    // create 6 pointers
    DLL *head1 = NULL;
    DLL *tail1 = NULL;

    DLL *head2 = NULL;
    DLL *tail2 = NULL;

    DLL *head3 = NULL;
    DLL *tail3 = NULL;

    // to insert values to DLL
    int len1 = strlen(num1);

    for (int i = len1 - 1; i >= 0; i--)
    {
        int digit = num1[i] - '0';
        insert_at_first_DLL(&head1, &tail1, digit);
    }

    int len2 = strlen(num2);

    for (int i = len2 - 1; i >= 0; i--)
    {
        int digit = num2[i] - '0';
        insert_at_first_DLL(&head2, &tail2, digit);
    }

    // to apply signs to head node
    if (neg1)
    {
        head1->data = -head1->data;
    }

    if (neg2)
    {
        head2->data = -head2->data;
    }

    // operation check
    if (strcmp(operator, "+") == 0)
    {

        int result = addition(&head1, &tail1, &head2, &tail2, &head3, &tail3);

        if (result == SUCCESS)
        {
            printf("ADDITION RESULT: ");
            print_data_DLL(head3);
        }
        else
        {
            printf("NO ADDITION PERFORMED\n");
        }
        return SUCCESS;
    }
    else if (strcmp(operator, "-") == 0)
    {
        int result = subtraction(&head1, &tail1, &head2, &tail2, &head3, &tail3);

        if (result == SUCCESS)
        {
            printf("SUBTRACTION RESULT: ");
            print_data_DLL(head3);
        }
        else
        {
            printf("NO SUBTRACTION PERFORMED\n");
        }
        return SUCCESS;
    }
    else if (strcmp(operator, "x") == 0)
    {
        int result = multiplication(&head1, &tail1, &head2, &tail2, &head3, &tail3);

        if (result == SUCCESS)
        {
            printf("MULTIPLICATION RESULT: ");
            print_data_DLL(head3);
        }
        else
        {
            printf("NO MULTIPLICATION PERFORMED\n");
        }
        return SUCCESS;
    }

    else if (strcmp(operator, "/") == 0)
    {
        int result = division(&head1, &tail1, &head2, &tail2, &head3, &tail3);
        int result_negative = neg1 ^ neg2;
        if (result == SUCCESS)
        {
            if (result_negative && head3->data != 0)
                head3->data = -(head3->data);
            printf("DIVISION RESULT: ");
            print_data_DLL(head3);
        }
        else
        {
            printf("NO DIVISION PERFORMED\n");
        }
        return SUCCESS;
    }
    else
    {
        // printf("Invalid operator. Use + - x /\n");
        error_arguments();
    }
    return SUCCESS;
}

void error_arguments()
{
    printf("ERROR: Invalid arguments.\n");
    printf("Usage: ./a.out <number1> <operator> <number2>\n");
    printf("Operators allowed: +  -  x  /\n");
    printf("Example: ./a.out 12345 + 67890\n");
}
