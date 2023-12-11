// Doubly Linked Lists Exercises
// ● Implement removal
// ● Implement insert after an item
// ● Implement insert before an item
// ● Higher Level Exercise: implement shuffling

// Include library --------------------------------------------------------
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ------------------------------------------------------------------------ 

// Define declaration -----------------------------------------------------
#define AIV_LIST(x) &(x.list_item)
#define AIV_PRINT_LIST(head) aiv_print_list((aiv_int_item*)head)
#define AIV_LIST_REMOVE(head, item) aiv_list_remove(&head, AIV_LIST(item))
// ------------------------------------------------------------------------ 

// Struct declaration -----------------------------------------------------
typedef struct aiv_list_item
{
    struct aiv_list_item *prev;
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
    }
    else
    {
        tail->next = item;
    }

    // Set prev
    item->prev = tail;

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
    if ((*head)->next != NULL)
    {
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
    else
    {
        *head = NULL;
    }

    // Set NULL on popped item node
    current_head->next = NULL;
    current_head->prev = NULL;

    return current_head;
}

int GetRandom(int min, int max) {
  
    // Generate and return a random number between min and max
    return rand() % (max - min + 1) + min;
}

void aiv_list_remove(aiv_list_item **head, aiv_list_item *item) 
{
    // Check if list is empty or item not found
    if (*head == NULL || item == NULL) 
    {
        printf("LIST IS EMPTY OR ITEM NOT FOUND\n");

        return; 
    }

    // Check if head
    if (item == *head) {
        *head = item->next;
    }

    // Update prev node
    if (item->prev != NULL) {
        item->prev->next = item->next;
    }

    // Update next node
    if (item->next != NULL) {
        item->next->prev = item->prev;
    }
}

void aiv_list_insert_after_byaddress(aiv_list_item **head, aiv_list_item *key, aiv_list_item *item) 
{
    // Check if list is empty
    if (!(*head))
    {
        return;
    }

    // Init vars
    aiv_list_item *current = *head;
    aiv_list_item *swap = NULL;

    while (current)
    {
        // Check match
        if (current == key)
        {
            swap = current->next;
            current->next = item;
            item->next = swap;
            item->prev = current;

            return;
        }
             
        // Update current node to next
        current = current->next;
    }
}

void aiv_list_insert_before_byaddress(aiv_list_item **head, aiv_list_item *key, aiv_list_item *item) 
{
    // Check if list is empty
    if (!(*head))
    {
        return;
    }

    // Init vars
    aiv_list_item *current = *head;
    aiv_list_item *swap = NULL;

    // Check if head
    if(current == key)
    {
        swap = current;
        *head = item;
        item->prev = NULL;
        item->next = swap;

        return;
    }

    while (current)
    {
        // Check match
        if (current->next == key)
        {
            swap = current->next;
            current->next = item;
            item->next = swap;
            item->prev = current;

            return;
        }
             
        // Update current node to next
        current = current->next;
    }
}

void aiv_list_insert_after_byindex(aiv_list_item **head, int index, aiv_list_item *item) 
{
    // Check if list is empty
    if (!(*head))
    {
        return;
    }

    // Init vars
    aiv_list_item *current = *head;
    aiv_list_item *swap = NULL;

    int counter = 1;

    while (current)
    {
        // Check match
        if (counter == index)
        {
            swap = current->next;
            current->next = item;
            item->next = swap;
            item->prev = current;

            return;
        }
        
        counter++;

        // Update current node to next
        current = current->next;
    }
}

void aiv_list_insert_before_byindex(aiv_list_item **head, int index, aiv_list_item *item) 
{
    // Check if list is empty
    if (!(*head))
    {
        return;
    }

    // Init vars
    aiv_list_item *current = *head;
    aiv_list_item *swap = NULL;

    int counter = 1;

    // Check if head
    if(counter == index)
    {
        swap = current;
        *head = item;
        item->prev = NULL;
        item->next = swap;

        return;
    }

    while (current)
    {
        // Check match
        if (counter + 1 == index)
        {
            swap = current->next;
            current->next = item;
            item->next = swap;
            item->prev = current;

            return;
        }

        counter++;
             
        // Update current node to next
        current = current->next;
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

void aiv_shuffle_list_byvalue(aiv_list_item **head)
{
    // Check if list is empty
    if (!head)
    {
        return;
    }

    // Get total items
    unsigned int total_items = aiv_list_length(*head);

    // Use the current time as a seed for randomness
    time_t unixTime;
    time(&unixTime);
    srand(unixTime);
      
    // Init vars
    aiv_list_item *current = *head;
    aiv_int_item *item_a = NULL;
    aiv_int_item *item_b = NULL;

    // Init temp vars
    int swap = 0;
    int shuffle = 1;
    int counter = 1;
    int random;

    while (shuffle <= (total_items / 2)) 
    {
        while (counter < total_items) 
        {    
            // Get random value
            random = GetRandom(0,2000000) % 2;
            
            // Check if set
            if (random != 0)
            {
                // Swap and reassign node
                item_a = (aiv_int_item*)current;
                item_b = (aiv_int_item*)current->next;

                swap = item_a->value;
                item_a->value = item_b->value;
                item_b->value = swap; 
            }

            // Update to next node
            current = current->next;

            // Update counter
            counter++;
        }

        // Update vars to next cycle
        current = *head;
        item_a = NULL;
        item_b = NULL;
        counter = 1;
        shuffle++;
    }
}

void aiv_shuffle_list_byaddress(aiv_list_item **head)
{
    // Check if list is empty
    if (!head)
    {
        return;
    }

    // Get total items
    unsigned int total_items = aiv_list_length(*head);
    
    // Use the current time as a seed for randomness
    time_t unixTime;
    time(&unixTime);
    srand(unixTime);
      
    // Init vars
    aiv_list_item *current;
    aiv_list_item *remove;

    int counter = 1;
    int randomCurr;
    int randomSet;

    for (int i = 0; i < total_items; i++)
    {
        // Init vars
        current = *head;
        remove = NULL;
        counter = 1;
        randomCurr = GetRandom(1, aiv_list_length(*head));

        while (current)
        {            
            // Check if match
            if (counter == randomCurr)
            {
                remove = current;
                aiv_list_remove(head, remove);

                current = *head;
                counter = 1;

                break;
            }

            // Update to nex node
            current = current->next;

            // Update counter
            counter++;
        }

        // Get random value
        randomSet = aiv_list_length(*head);

        while (current)
        {            
            if (counter == randomSet)
            {
                aiv_list_insert_after_byaddress(head, current, remove);

                break;
            }

            // Update to nex node
            current = current->next;

            // Update counter
            counter++;
        }
    }
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

    printf("------------------------------------------\n");  
    // Print list
    AIV_PRINT_LIST(head);

    // Shuffle list
    //printf("SHUFFLED LIST BY ADDRESS\n");
    //printf("------------------------------------------\n");  
    //aiv_shuffle_list_byaddress(&head);

    // Print list
    //AIV_PRINT_LIST(head);

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

    // Append to list
    aiv_list_append(&head, AIV_LIST(int_first));
    aiv_list_append(&head, AIV_LIST(int_second));
    aiv_list_append(&head, AIV_LIST(int_third));

    // Repopulate list
    printf("REPOPULATE LIST\n");
    printf("------------------------------------------\n");  

    // Print list
    AIV_PRINT_LIST(head);

    printf("INSERT VALUE %d BEFORE %d\n", int_fourth.value, int_third.value);  
    aiv_list_insert_before_byaddress(&head, AIV_LIST(int_third), AIV_LIST(int_fourth));
    printf("------------------------------------------\n");  

    // Print list
    AIV_PRINT_LIST(head);

    aiv_int_item int_fifth;
    int_fifth.value = 5;
    printf("INSERT VALUE %d AFTER %d\n", int_fifth.value, int_first.value);  
    aiv_list_insert_after_byaddress(&head, AIV_LIST(int_first), AIV_LIST(int_fifth));
    printf("------------------------------------------\n"); 

    // Print list
    AIV_PRINT_LIST(head);

    aiv_int_item int_sixty;
    int_sixty.value = 6;
    int index = 5;
    printf("INSERT VALUE %d AFTER INDEX: %d\n", int_sixty.value, index);  
    aiv_list_insert_after_byindex(&head, index, AIV_LIST(int_sixty));
    printf("------------------------------------------\n"); 

    // Print list
    AIV_PRINT_LIST(head);

    aiv_int_item int_seventy;
    int_seventy.value = 7;
    printf("INSERT VALUE %d BEFORE INDEX: %d\n", int_seventy.value, index);  
    aiv_list_insert_before_byindex(&head, index, AIV_LIST(int_seventy));
    printf("------------------------------------------\n"); 

    // Print list
    AIV_PRINT_LIST(head);

    // Shuffle list
    printf("SHUFFLED LIST BY VALUE\n");
    printf("------------------------------------------\n");  
    aiv_shuffle_list_byvalue(&head);

    // Print list
    AIV_PRINT_LIST(head);

    // End of program
    printf("\nEND -------------------------------------------------\n");

    return 0;
}
// ------------------------------------------------------------------------
