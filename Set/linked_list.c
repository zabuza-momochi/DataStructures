// Include Header -----------------------------------------------------------
#include "set.h"
// -------------------------------------------------------------------------- 

// Function declaration -----------------------------------------------------
aiv_list_item *aiv_list_get_tail(aiv_list_item *head)
{
    // Check if list is empty
    if (!head)
    {
        return NULL;
    }

    // Set items
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

void aiv_print_list(aiv_set_item *head)
{
    // Check if list is empty
    if (!head)
    {
        printf("EMPTY BLOCK\n");  
        return;
    }

    // Set list items
    aiv_set_item *my_list = head;

    while (my_list)
    {
        printf("KEY: %s\n", my_list->key);
        
        // Update to next node
        my_list = (aiv_set_item *)my_list->list_item.next;
    }
    printf("-------------------\n");  
}
// ------------------------------------------------------------------------
