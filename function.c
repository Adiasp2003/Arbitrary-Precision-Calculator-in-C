#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int addition(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3)
{
    // check signs based on number < 0
    int sign1 = ((*head1)->data < 0) ? -1 : 1;
    int sign2 = ((*head2)->data < 0) ? -1 : 1;

    // save old data
    int old1 = (*head1)->data;
    int old2 = (*head2)->data;

    (*head1)->data = abs((*head1)->data);
    (*head2)->data = abs((*head2)->data);

    int result_negative = 0;

    // CASE 1: (+A) + (+B) = A + B
    if (sign1 == 1 && sign2 == 1)
    {
        result_negative = 0;
    }
    // CASE 2: (-A) + (-B) = -(A + B)
    else if (sign1 == -1 && sign2 == -1)
    {
        result_negative = 1;
    }
    // CASE 3: (+A) + (-B) = A - B
    else if (sign1 == 1 && sign2 == -1)
    {
        int cmp = compare_DLL(head1, head2);

        if (cmp == 0) // if both numbers are same(A=B)
        {
            insert_at_first_DLL(head3, tail3, 0);
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
        else if (cmp == 1) // A > B
        {
            subtraction(head1, tail1, head2, tail2, head3, tail3);
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
        else // B > A
        {
            subtraction(head2, tail2, head1, tail1, head3, tail3);
            if (*head3)
                (*head3)->data = -abs((*head3)->data);
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
    }
    // CASE 4: (-A) + (+B) = B - A
    else if (sign1 == -1 && sign2 == 1)
    {
        int cmp = compare_DLL(head1, head2);

        if (cmp == 0) // (A=B)
        {
            insert_at_first_DLL(head3, tail3, 0);
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
        else if (cmp == -1) // B > A
        {
            subtraction(head2, tail2, head1, tail1, head3, tail3);
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
        else // A > B
        {
            subtraction(head1, tail1, head2, tail2, head3, tail3);
            if (*head3)
                (*head3)->data = -abs((*head3)->data);
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
    }

    // normal Addition operation logic
    DLL *temp1 = *tail1; // temp pointing to tail to start operation from tail - 1 node
    DLL *temp2 = *tail2;

    int carry = 0; // initally carrry to be 0
    int sum = 0;

    while (temp1 || temp2) // check for temp1 or temp2
    {
        int d1 = temp1 ? abs(temp1->data) : 0;
        int d2 = temp2 ? abs(temp2->data) : 0;

        sum = d1 + d2 + carry;

        carry = sum / 10;
        int digit = sum % 10;                     // fetch last bit
        insert_at_first_DLL(head3, tail3, digit); // insert result into list 3

        if (temp1)
            temp1 = temp1->prev; // move to previous node after operation

        if (temp2)
            temp2 = temp2->prev; // move to previous node after operation
    }

    if (carry == 1) // print remaining carry
        insert_at_first_DLL(head3, tail3, carry);

    // Apply result sign
    if (result_negative && *head3)
        (*head3)->data = -abs((*head3)->data);

    // Restore original signs
    (*head1)->data = old1;
    (*head2)->data = old2;

    return SUCCESS;
}

int subtraction(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3)
{
    // check sign based on number < 0
    int sign1 = ((*head1)->data < 0) ? -1 : 1;
    int sign2 = ((*head2)->data < 0) ? -1 : 1;

    int is_negative = 0;

    // Make heads positive TEMPORARILY for absolute operations
    int old1 = (*head1)->data;
    int old2 = (*head2)->data;

    // convert first digit to absolute value
    (*head1)->data = abs((*head1)->data);
    (*head2)->data = abs((*head2)->data);

    // if (+A) -(-B) = A+B
    if (sign1 == 1 && sign2 == -1)
    {
        addition(head1, tail1, head2, tail2, head3, tail3);

        // restore original signs
        (*head1)->data = old1;
        (*head2)->data = old2;
        return SUCCESS;
    }

    // if (-A) -(+B) = -(A+B)
    if (sign1 == -1 && sign2 == 1)
    {
        addition(head1, tail1, head2, tail2, head3, tail3);
        // if result negative
        if (*head3)
            (*head3)->data = -((*head3)->data);

        // restore original signs
        (*head1)->data = old1;
        (*head2)->data = old2;
        return SUCCESS;
    }

    // if (-A) -(-B) = B-A
    if (sign1 == -1 && sign2 == -1)
    {
        int cmp = compare_DLL(head1, head2); // to compare A and B

        if (cmp == 0)
        {
            //(-A) -(-A) = 0
            insert_at_first_DLL(head3, tail3, 0);
            // restore original signs
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }

        else if (cmp == -1) // B > A
        {
            // B-A(result positive)
            swap_DLL(head1, tail1, head2, tail2);
            is_negative = 0; // positive result
        }
        else // A>B
        {
            //-(A-B)
            is_negative = 1; // negative result
        }
    }

    else
    {
        // CASE 4: (+A) - (+B)
        int cmp = compare_DLL(head1, head2);

        if (cmp == 0)
        {
            insert_at_first_DLL(head3, tail3, 0);
            // restore original signs
            (*head1)->data = old1;
            (*head2)->data = old2;
            return SUCCESS;
        }
        else if (cmp == -1)
        {
            // if A<B , negative result, so swap
            is_negative = 1;
            swap_DLL(head1, tail1, head2, tail2);
        }
    }

    // normal subtraction logic
    DLL *temp1 = *tail1; // temp pointing to tail to start operation from tail - 1 node
    DLL *temp2 = *tail2;

    int borrow = 0; // for borrowing a value from previous digit

    while (temp1 != NULL || temp2 != NULL)
    {
        int digit1 = temp1 ? abs(temp1->data) : 0;
        int digit2 = temp2 ? abs(temp2->data) : 0;

        digit1 = digit1 - borrow;

        if (digit1 < digit2)
        {
            digit1 = digit1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int difference = digit1 - digit2;

        insert_at_first_DLL(head3, tail3, difference);

        if (temp1)
            temp1 = temp1->prev;

        if (temp2)
            temp2 = temp2->prev;
    }
    // remove leading zeros
    DLL *temp = *head3;
    while (temp && temp->data == 0 && temp->next != NULL)
    {
        delete_at_first_DLL(head3, tail3);
        temp = *head3;
    }

    if (is_negative == 1 && *head3)
    {
        // if (*head3 != NULL)
        (*head3)->data = -abs((*head3)->data);
    }
    // restore original signs
    (*head1)->data = old1;
    (*head2)->data = old2;

    return SUCCESS;
}

int multiplication(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3)
{
    // to detect sign for both numbers
    int sign1 = ((*head1)->data < 0) ? -1 : 1;
    int sign2 = ((*head2)->data < 0) ? -1 : 1;

    // both different signs then negative result
    int result_negative = (sign1 != sign2);

    // Make numbers positive for further process
    (*head1)->data = abs((*head1)->data);
    (*head2)->data = abs((*head2)->data);

    DLL *temp2 = *tail2; // iterate from last digit of num2
    int pos = 0;         // to shift partial result

    *head3 = *tail3 = NULL;               // initialize head and tail with NULL
    insert_at_first_DLL(head3, tail3, 0); // tail 3 with 0

    while (temp2)
    {
        int digit2 = abs(temp2->data); // current digit of num2

        // each iteration builds partial result
        DLL *partial_head = NULL;
        DLL *partial_tail = NULL;

        DLL *temp1 = *tail1; // temp1 iterate from last digit
        int carry = 0;

        // multiply digit2 with entire num1
        while (temp1)
        {
            int digit1 = abs(temp1->data);
            int multiply = digit1 * digit2 + carry;

            insert_at_first_DLL(&partial_head, &partial_tail, multiply % 10);
            carry = multiply / 10;

            temp1 = temp1->prev;
        }

        // to insert last carry if present
        if (carry)
            insert_at_first_DLL(&partial_head, &partial_tail, carry);

        // add zeros at the end as in normal written multiplication calculation
        for (int k = 0; k < pos; k++)
        {
            insert_at_last_DLL(&partial_head, &partial_tail, 0);
        }

        // add partial result to main result stored in head3
        DLL *sum_head = NULL;
        DLL *sum_tail = NULL;

        addition(&partial_head, &partial_tail, head3, tail3, &sum_head, &sum_tail);

        // free old result and update new result
        free_DLL(head3, tail3);
        *head3 = sum_head;
        *tail3 = sum_tail;

        // move to next digit
        temp2 = temp2->prev;
        pos++; // new partial result will have more number of zeros
    }

    // remove leading zeros in final result
    DLL *temp = *head3;
    while (temp && temp->data == 0 && temp->next != NULL)
    {
        delete_at_first_DLL(head3, tail3);
        temp = *head3;
    }
    // Apply Sign at the end of multiplication
    if (result_negative && *head3 && !((*head3)->data == 0 && (*head3)->next == NULL))
    {
        (*head3)->data = -abs((*head3)->data);
    }
    return SUCCESS;
}

int division(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3)
{
    int negative1 = 0;
    int negative2 = 0;

    // detect signs but not modify values
    if ((*head1)->data < 0)
        negative1 = 1;

    if ((*head2)->data < 0)
        negative2 = 1;

    // remove the sign from only the first digit
    if (negative1)
        (*head1)->data = ((*head1)->data * -1); // make positive manually

    if (negative2)
        (*head2)->data = ((*head2)->data * -1);

    int result_negative_no = negative1 ^ negative2; // user XOR

    // check divisor = 0

    DLL *temp = *head2;
    int divisorisZero = 1;
    while (temp)
    {
        if (temp->data != 0)
        {
            divisorisZero = 0;
            break;
        }
        temp = temp->next;
    }

    if (divisorisZero == 1)
    {
        printf("Error: Divisor is Zero\n");
        return FAILURE;
    }

    // check dividend = 0

    temp = *head1;
    int dividendZero = 1;

    while (temp)
    {
        if (temp->data != 0)
        {
            dividendZero = 0;
            break;
        }
        temp = temp->next;
    }

    if (dividendZero == 1)
    {
        insert_at_first_DLL(head3, tail3, 0);
        return SUCCESS;
    }

    // Now the addition logic 20 + 0

    DLL *sum_head = NULL;
    DLL *sum_tail = NULL;

    insert_at_first_DLL(&sum_head, &sum_tail, 0); // intially 20 + 0

    int count = 0;

    while (1)
    {
        DLL *new_sum_head = NULL;
        DLL *new_sum_tail = NULL;

        addition(&sum_head, &sum_tail, head2, tail2, &new_sum_head, &new_sum_tail);

        free_DLL(&sum_head, &sum_tail);

        sum_head = new_sum_head;
        sum_tail = new_sum_tail;

        count++; // to return the final result

        int cmp = compare_DLL(&sum_head, head1);

        if (cmp == 0)
        {
            break; // sum == dividend
        }

        else if (cmp == 1) // undo last addition 120 - 20
        {
            DLL *undo_head = NULL;
            DLL *undo_tail = NULL;

            subtraction(&sum_head, &sum_tail, head2, tail2, &undo_head, &undo_tail);

            free_DLL(&sum_head, &sum_tail);

            sum_head = undo_head;
            sum_tail = undo_tail;

            count--; // to decrement one addition count value

            break;
        }
    }

    // if no count or just no division
    if (count == 0)
    {
        insert_at_first_DLL(head3, tail3, 0);
    }

    // just the counted division value
    else
    {
        while (count > 0)
        {
            int digit = count % 10;
            insert_at_first_DLL(head3, tail3, digit);
            count = count / 10;
        }
    }
    free_DLL(&sum_head, &sum_tail);

    // applying sign to result
    if (result_negative_no && (*head3)->data != 0)
    {
        (*head3)->data = -((*head3)->data);
    }
    // restore original signs
    (*head1)->data = negative1 ? -abs((*head1)->data) : abs((*head1)->data);
    (*head2)->data = negative2 ? -abs((*head2)->data) : abs((*head2)->data);

    return SUCCESS;
}