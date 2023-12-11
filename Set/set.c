// Sets Exercises
// ● Implement search
// ● Implement removal
// ● Implement unique keys
// ● Higher Level Exercise: refactor code to allow the set implementation to reuse
// the linked list implementation

// Include Header -----------------------------------------------------------
#include "set.h"
// -------------------------------------------------------------------------- 

// Function declaration -----------------------------------------------------
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void aiv_increment_counter(aiv_set *set, int index)
{
    set->counter_list[index]++;
}

void aiv_decrement_counter(aiv_set *set, int index)
{
    set->counter_list[index]--;
}

void aiv_set_insert(aiv_set *set, const char *key)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE_DEFAULT;

    printf("-----------------------------------------------------\n");
    printf("HASH OF: %s = %llu WITH INDEX: %llu\n", key, hash, index);

    // Get current list
    aiv_list_item *current = set->hashmap[index].next;
    
    // Get total items of list
    const int counter_list = set->counter_list[index];

    // Check if key already exists
    if (aiv_check_duplicate(set, key))
    {
        printf("ITEM: %s ALREADY EXISTS \n", key);
        printf("INSERT FAILED! \n");

        return;   
    }

    // Check if index is empty or there is a free block
    if (current == NULL || counter_list < HASHMAP_SIZE_LIST)
    {
        // Allocate new item
        aiv_set_item *new_item = malloc(sizeof(aiv_set_item));
        
        // Check if malloc failed
        if (!new_item)
        {
            printf("ERROR TO ALLOCATE ITEM");

            return;
        }

        // Init new item
        new_item->key = key;
        new_item->key_len = key_len;

        // Append item struct to list
        aiv_list_append(&(set->hashmap[index].next), &(new_item->list_item));
        
        // Update counter
        aiv_increment_counter(set, index);

        printf("ITEM %s STORED AT INDEX: %llu SLOT: %d\n", new_item->key, index, set->counter_list[index]);       
        printf("%d/%d BLOCKS\n", set->counter_list[index], HASHMAP_SIZE_LIST);        

        return;
    }

    // No empty blocks, collision!
    printf("COLLISION! NO EMPTY BLOCKS %d/%d\n",set->counter_list[index], HASHMAP_SIZE_LIST);   
}

aiv_set_item *aiv_set_find(aiv_set *set, const char *key)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE_DEFAULT;

    printf("-----------------------------------------------------\n");
    printf("FIND: %s WITH INDEX: %llu\n", key, index);

    // Set current node
    aiv_list_item *current_node = set->hashmap[index].next;

    for (size_t i = 1; i <= HASHMAP_SIZE_LIST; i++)
    {
        // Chech if node exists
        if (current_node != NULL)
        {
            // Set current item
            aiv_set_item *current_item = (aiv_set_item*)current_node;

            // Check if key exists
            if (current_item->key_len > 0)
            {
                printf("COMPARE ITEM: %s\n", current_item->key);

                // Check if keys match
                if (current_item->key_len == key_len && !memcmp(current_item->key, key, key_len))
                {
                    printf("FOUND! KEY: %s AT INDEX: %llu SLOT: %llu\n", key, index, i);

                    return current_item;
                }
            }

            // Update to next node
            current_node = current_node->next;
        }
    }

    printf("ITEM %s NOT FOUND!\n", key);

    return NULL;
}

int aiv_check_duplicate(aiv_set *set, const char *key)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE_DEFAULT;

    // Set current node
    aiv_list_item *current_node = set->hashmap[index].next;

    for (size_t i = 1; i <= HASHMAP_SIZE_LIST; i++)
    {
        // Check if node exists
        if (current_node != NULL)
        {
            // Set current item
            aiv_set_item *current_item = (aiv_set_item*)current_node;

            // Check if key exists
            if (current_item->key_len > 0)
            {
                // Check if keys match
                if (current_item->key_len == key_len && !memcmp(current_item->key, key, key_len))
                {
                    // Return true
                    return 1;
                }
            }

            // Update to next node
            current_node = current_node->next;
        }
    }

    // Return false
    return 0;
}

aiv_set_item *aiv_set_remove(aiv_set *set, const char *key)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE_DEFAULT;

    printf("-----------------------------------------------------\n");
    printf("REMOVE: %s WITH INDEX: %llu\n", key, index);

    // Set current node
    aiv_list_item *current_node = set->hashmap[index].next;

    for (size_t i = 1; i <= HASHMAP_SIZE_LIST; i++)
    {
        // Check if node exists
        if (current_node != NULL)
        {
            // Set current item
            aiv_set_item *current_item = (aiv_set_item*)current_node;

            // Check if key exists
            if (current_item->key_len > 0)
            {
                // Check if key exists
                if (current_item->key_len == key_len && !memcmp(current_item->key, key, key_len))
                {
                    // Update counter
                    aiv_decrement_counter(set, index);

                    // Remove item from linked list
                    aiv_list_remove(&(set->hashmap[index].next), &(current_item->list_item));

                    printf("REMOVED: %s AT INDEX %llu SLOT %llu\n", key, index, i);
                    printf("%d/%d BLOCKS\n", set->counter_list[index], HASHMAP_SIZE_LIST);        

                    return current_item;
                }
            }

            // Update to next node
            current_node = current_node->next;
        }
    }

    printf("KEY: %s WITH THIS VALUE NOT FOUND!\n", key);

    return NULL;
}

void aiv_set_print(aiv_set *set)
{
    printf("PRINT SET\n");
    printf("-------------------\n");

    for (size_t i = 0; i < HASHMAP_SIZE_DEFAULT; i++)
    {
        printf("ITEMS AT INDEX[%llu]:\n", i);  
        aiv_print_list((aiv_set_item*)set->hashmap[i].next);
    }   
}
// -------------------------------------------------------------------------- 

// Entry point -------------------------------------------------------------- 
int main(int argc, char **argv)
{
    // Declaration
    aiv_set myset;
    
    // Reset values
    memset(&myset, 0, sizeof(aiv_set));

    // Insert item
    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Ciao");
    aiv_set_insert(&myset, "Good");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Never");
    printf("-----------------------------------------------------\n");

    // Print set
    aiv_set_print(&myset);

    // Find item
    printf("TRY FIND ITEM\n");
    aiv_set_find(&myset, "Ciao");
    
    // Remove item
    printf("-----------------------------------------------------\n");
    printf("TRY REMOVE ITEM\n");
    aiv_set_remove(&myset, "Hello");

    // Print set
    printf("-----------------------------------------------------\n");
    aiv_set_print(&myset);

    // Insert
    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Ciao");

    // Print set
    printf("-----------------------------------------------------\n");
    aiv_set_print(&myset);

    // End of program
    printf("\nEND -------------------------------------------------\n");

    return 0;
}
// -------------------------------------------------------------------------- 
