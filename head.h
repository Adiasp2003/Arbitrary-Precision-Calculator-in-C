#ifndef Header
#define Header

#define SUCCESS 0
#define FAILURE 1

typedef int data;
typedef struct node
{
    data data;
    struct node *prev;
    struct node *next;

} DLL;

void error_arguments();
int insert_at_first_DLL(DLL **head, DLL **tail, int num);
int insert_at_last_DLL(DLL **head, DLL **tail, int num);
void print_data_DLL(DLL *head);

int addition(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3);
int subtraction(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3);
int multiplication(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3);
int division(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3);

int free_DLL(DLL **, DLL **);
int compare_DLL(DLL **, DLL **);
int swap_DLL(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2);
int delete_at_first_DLL(DLL **head, DLL **tail);
#endif