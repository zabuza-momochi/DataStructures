// Linked Lists Exercises
// ● Implement removal of item
// ● Use preprocessor directives to reduce the verbose casting
// ● Higher Level Exercise: implement reversing of the list

// Include library --------------------------------------------------------
#include <stddef.h>
#include <stdio.h>
// ------------------------------------------------------------------------ 

// Define declaration -----------------------------------------------------
#define AIV_LIST(x) &(x.list_item)
#define AIV_PRINT_LIST(head) aiv_print_list((aiv_int_item*)head)
#define AIV_LIST_REMOVE(head, item) aiv_list_remove(&head, AIV_LIST(item))
// ------------------------------------------------------------------------ 

// Struct declaration -----------------------------------------------------
typedef struct aiv_list_item
{
    struct aiv_list_item *next;
}aiv_list_item;

typedef struct aiv_int_item
{
    struct aiv_list_item list_item;
    int value;
}aiv_int_item;
// ------------------------------------------------------------------------

// Method declaration -----------------------------------------------------
aiv_list_item *aiv_list_get_tail(aiv_list_item *head)
{
    // Check if list is empty
    if (!head)
    {
        return NULL;
    }

    aiv_list_item *current_item = head;
    aiv_list_item *last_item = head;

    while (current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
}

aiv_list_item *aiv_list_append(aiv_list_item **head, aiv_list_item *item) 
{
    // Get tail
    aiv_list_item *tail = aiv_list_get_tail(*head);

    // Check if tail is empty
    if (!tail)
    {
        *head = item;
        tail = *head;
    }
    else
    {
        tail->next = item;
    }

    // set NULL last node
    item->next = NULL;
    return item;
}

aiv_list_item *aiv_list_pop(aiv_list_item **head) 
{
    // Check if list is empty
    if (!(*head))
    {
        return NULL;
    }

    // Init current head
    aiv_list_item *current_head = *head;

    // Change head with next item
    *head = (*head)->next;

    // Set NULL on popped item node
    current_head->next = NULL;

    return current_head;
}

void aiv_list_remove(aiv_list_item **head, aiv_list_item *item) 
{
    // Check if list is empty
    if (!(*head)) 
    {
        printf("LIST IS EMPTY OR ITEM NOT FOUND\n");

        return;
    }

    // Check if remove head
    if (*head == item) 
    {
        // Reassign head to next node
        *head = (*head)->next;

        return;
    }

    // Set current item (head)
    aiv_list_item *current_item = *head;

    // Scroll nodes list
    while (current_item->next && current_item->next != item) 
    {
        // Update to next node
        current_item = current_item->next;
    }

    // Check if match
    if (current_item->next == item) 
    {
        // Link next node below removed node
        current_item->next = current_item->next->next;
    } 
    else 
    {
        printf("ITEM NOT FOUND\n");
    }
}

unsigned int aiv_list_length(aiv_list_item *head)
{
    // Init counter
    unsigned int counter = 0;

    // Set current item
    aiv_list_item *current_item = head;

    while (current_item)
    {
        // Update counter
        counter++;

        // Update to next node
        current_item = current_item->next;
    }

    return counter;
}

void aiv_reverse_list(aiv_list_item **head)
{
    // Check if list is empty
    if (!head)
    {
        return;
    }

    // Init vars
    aiv_list_item *current = *head;
    aiv_list_item *prev = NULL;
    aiv_list_item *next = NULL;

    while (current != NULL) 
    {
        next = current->next;  // Save next node
        current->next = prev;  // Reverse node link
        prev = current;        // Update prev node
        current = next;        // Update current node
    }

    *head = prev;  // Set last node as new head
}

void aiv_print_list(aiv_int_item *head)
{
    // Check if list is empty
    if (!head)
    {
        printf("LIST IS EMPTY\n");  
        return;
    }

    // Set list items
    aiv_int_item *my_list = head;

    printf("PRINT ITEMS OF LIST\n");  
    while (my_list)
    {
        printf("Item value: %d\n", my_list->value);

        // Update to next node
        my_list = (aiv_int_item *)my_list->list_item.next;
    }
    printf("------------------------------------------\n");  

    // Print list length
    printf("LIST LENGTH: %d\n", aiv_list_length((aiv_list_item*)head));
    printf("------------------------------------------\n");  
}
// ------------------------------------------------------------------------

// Entry Point ------------------------------------------------------------
int main(int argc, char** argv)
{
    // Init list
    aiv_list_item *head = NULL;
    
    // Init values
    aiv_int_item int_first;
    int_first.value = 1;

    aiv_int_item int_second;
    int_second.value = 2;

    aiv_int_item int_third;
    int_third.value = 3;

    aiv_int_item int_fourth;
    int_fourth.value = 4;

    // Append to list
    aiv_list_append(&head, AIV_LIST(int_first));
    aiv_list_append(&head, AIV_LIST(int_second));
    aiv_list_append(&head, AIV_LIST(int_third));
    aiv_list_append(&head, AIV_LIST(int_fourth));

    // Print list
    printf("------------------------------------------\n");  
    AIV_PRINT_LIST(head);

    // Remove item from list
    printf("REMOVED ITEM %d FROM LIST\n", int_first.value);  
    aiv_list_remove(&head, AIV_LIST(int_first));
    printf("------------------------------------------\n");  

    // Print list
    AIV_PRINT_LIST(head);

    // Pop item from list
    aiv_int_item *pop = (aiv_int_item*)aiv_list_pop(&head);
    printf("POP ITEM %d FROM LIST\n", pop->value);  
    printf("------------------------------------------\n");  

    // Print list
    AIV_PRINT_LIST(head);

    // Remove item from list
    printf("REMOVED ITEM %d FROM LIST\n", int_fourth.value);  
    aiv_list_remove(&head, AIV_LIST(int_fourth));
    printf("------------------------------------------\n");  
   
    // Print list
    AIV_PRINT_LIST(head);

    // Pop item from list
    pop = (aiv_int_item*)aiv_list_pop(&head);
    printf("POP ITEM %d FROM LIST\n", pop->value);  
    printf("------------------------------------------\n");  
   
    // Print list
    AIV_PRINT_LIST(head);

    aiv_list_append(&head, AIV_LIST(int_first));
    aiv_list_append(&head, AIV_LIST(int_second));
    aiv_list_append(&head, AIV_LIST(int_third));
    printf("REPOPULATE LIST\n");
    printf("------------------------------------------\n");  

    // Print list
    AIV_PRINT_LIST(head);

    // Reverse list
    aiv_reverse_list(&head);
    printf("REVERSED LIST\n");
    printf("------------------------------------------\n");  

    // Print list
    AIV_PRINT_LIST(head);

    // End of program
    printf("\nEND -------------------------------------------------\n");

    return 0;
}
// ------------------------------------------------------------------------
