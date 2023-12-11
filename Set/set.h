// Include library --------------------------------------------------------
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// ------------------------------------------------------------------------ 

// Define declaration -----------------------------------------------------
#define HASHMAP_SIZE_DEFAULT 3
#define HASHMAP_SIZE_LIST 2

#define AIV_LIST(x) &(x.list_item)
#define AIV_PRINT_LIST(head) aiv_print_list((aiv_int_item*)head)
#define AIV_LIST_REMOVE(head, item) aiv_list_remove(&head, AIV_LIST(item))
// ------------------------------------------------------------------------ 

// Struct declaration -----------------------------------------------------
#ifndef SETSTRUCT_H
#define SETSTRUCT_H

typedef struct aiv_list_item
{
    struct aiv_list_item *next;
}aiv_list_item;

typedef struct aiv_set_item
{
    struct aiv_list_item list_item;
    const char *key;
    size_t key_len;
}aiv_set_item;

typedef struct aiv_set
{
    struct aiv_list_item hashmap[HASHMAP_SIZE_DEFAULT];
    int counter_list[HASHMAP_SIZE_LIST];
}aiv_set;
#endif
// ------------------------------------------------------------------------

// Function declaration -----------------------------------------------------
aiv_list_item *aiv_list_get_tail(aiv_list_item *head);

aiv_list_item *aiv_list_append(aiv_list_item **head, aiv_list_item *item);

aiv_list_item *aiv_list_pop(aiv_list_item **head);

aiv_set_item *aiv_set_find(aiv_set *set, const char *key);

aiv_set_item *aiv_set_remove(aiv_set *set, const char *key);

unsigned int aiv_list_length(aiv_list_item *head);

void aiv_reverse_list(aiv_list_item **head);

void aiv_print_list(aiv_set_item *head);

void aiv_list_remove(aiv_list_item **head, aiv_list_item *item);
 
int aiv_check_duplicate(aiv_set *set, const char *key);
// ------------------------------------------------------------------------