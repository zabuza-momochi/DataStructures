// Include Header -----------------------------------------------------------
#include "dictionary.h"
// ------------------------------------------------------------------------ 

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

aiv_set *aiv_set_init(aiv_set *set, int size)
{
    printf("-----------------------------------------------------\n");

    // Init dictionary
    memset(set, 0, sizeof(aiv_set));

    // Check if size is set
    if (size <= 0)
    {
        // Default value
        size = HASHMAP_SIZE_DEFAULT;
    }

    // Allocate memory for array
    set->hashmap = malloc(sizeof(aiv_list_item) * size);
    set->counter_list = malloc(sizeof(int) * size);

    // Check if malloc failed
    if (!set->hashmap || !set->counter_list)
    {
        // Free unused memory
        free(set);

        return NULL;
    }

    // Set size of dictionary
    (*set).capacity = size;

    // Reset values
    memset((*set).hashmap, 0, sizeof(aiv_list_item) * size);
    memset((*set).counter_list, 0, sizeof(int) * size);

    printf("INIT OF NEW DICTIONARY OK!\n");

    return set;
}

aiv_set *aiv_set_rehash(aiv_set *set)
{
    // Set capacity
    const int old_capacity = set->capacity;
    const int new_capacity = old_capacity * 2;

    // Declare new dictionary
    aiv_set new_set;
    
    // Init new dictionary
    aiv_set_init(&new_set, new_capacity);

    for (size_t i = 0; i < old_capacity; i++)
    {
        // Set current node
        aiv_list_item *current_node = set->hashmap[i].next;

        // Check if node exists
        while (current_node != NULL)
        {
            // Set current item
            aiv_set_item *current_item = (aiv_set_item*)current_node;

            // Check if key exists
            if (current_item->key_len > 0)
            {         
                // Insert item           
                aiv_set_insert(&new_set, current_item->key, current_item->value, current_item->type_data);
            }

            // Update to next node
            current_node = current_item->list_item.next;
        }
    }

    // Check if filled
    if (set->hashmap != NULL ) 
    {
        // Free old memory
        free(set->hashmap);
        free(set->counter_list);
    }

    // Allocate memory for array with new capacity
    set->hashmap = malloc(sizeof(aiv_list_item) * new_capacity);
    set->counter_list = malloc(sizeof(int) * new_capacity);

    // Check if malloc failed
    if (!set->hashmap || !set->counter_list)
    {
        // Free unused memory
        free(set);
        
        return NULL;
    }

    // Copy rehashed array map
    memcpy(set->hashmap, new_set.hashmap, sizeof(aiv_list_item) * new_capacity);
    memcpy(set->counter_list, new_set.counter_list, sizeof(int) * new_capacity);

    // Copy remaining fields
    (*set).collision_counter = new_set.collision_counter;
    (*set).capacity = new_set.capacity;

    // Free unused memory
    free(new_set.counter_list);
    free(new_set.hashmap);

    return set;   
}

void aiv_set_insert(aiv_set *set, const char *key, const void *value, const int type_data)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*set).capacity;

    printf("-----------------------------------------------------\n");

    // Check if limit collision reached
    if (set->collision_counter >= (*set).capacity / 2)
    {
        printf("COLLISION LIMIT REACHED! REHASH OF DICTIONARY\n");
        
        // Check if rehash not failed
        if (aiv_set_rehash(set))
        {
            printf("-----------------------------------------------------\n");
            printf("REHASH COMPLETE! DICTIONARY SIZE INCREASED TO: %d\n", set->capacity);

            return;
        }
        else // Rehash failed
        {
            printf("-----------------------------------------------------\n");
            printf("REHASH FAILED! SPACE NOT AIVALABLE\n");

            return;           
        }
    }

    // Switch type 0 = INT | 1 CHAR[]
    switch (type_data)
    {
        // INT case
        case 0:
            printf("HASH OF: %s = %llu WITH INDEX: %llu AND VALUE: %d\n", key, hash, index,  *(int *)(value));
        break;

        // CHAR case
        case 1:
            printf("HASH OF: %s = %llu WITH INDEX: %llu AND VALUE: %s\n", key, hash, index, (char *)(value));
        break;
    }

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
        // Allocate memory for new item
        aiv_set_item *new_item = malloc(sizeof(aiv_set_item));
        
        // Check if malloc failed
        if (!new_item)
        {
            printf("ERROR TO ALLOCATE ITEM");

            return;
        }

        // Fill values
        new_item->key = key;
        new_item->key_len = key_len;
        new_item->value = (void*)value;
        new_item->type_data = type_data;

        // Append item struct to list
        aiv_list_append(&(set->hashmap[index].next), &(new_item->list_item));

        // Update counter
        aiv_increment_counter(set, index);

        printf("ITEM %s STORED AT INDEX: %llu SLOT: %d\n", new_item->key, index, set->counter_list[index]);       
        printf("%d/%d BLOCKS\n", set->counter_list[index], HASHMAP_SIZE_LIST);        

        return;
    }

    // No empty blocks, collision!
    aiv_set_item *current_item = (aiv_set_item*)current;

    printf("COLLISION! NO EMPTY BLOCKS %d/%d\n",set->counter_list[index], HASHMAP_SIZE_LIST);

    // Update collision
    set->collision_counter += 1;
}

aiv_set_item *aiv_set_find(aiv_set *set, const char *key, const void *value)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*set).capacity;

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
                    // Set type value
                    const int type_data = current_item->type_data;

                    // Switch type 0 = INT | 1 CHAR[]
                    switch (type_data)
                    {
                        // INT case
                        case 0:

                            // Check if values match
                            if (*(int *)(current_item->value) == *(int *)(value))
                            {
                                printf("FOUND! KEY: %s VALUE: %d AT INDEX: %llu SLOT: %llu\n", key, *(int *)(current_item->value), index, i);
                            }

                            return current_item;

                        break;
                        
                        // CHAR case
                        case 1:

                            // Check if values match
                            if ((char *)(current_item->value) == (char *)(value))
                            {
                                printf("FOUND! KEY: %s VALUE: %s AT INDEX: %llu SLOT: %llu\n", key, (char *)(current_item->value), index, i);
                            }

                            return current_item;

                        break;
                    }     
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
    const size_t index = hash % (*set).capacity;

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

aiv_set_item *aiv_set_remove(aiv_set *set, const char *key, const void *value)
{
    // Set const vars
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*set).capacity;

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
                    // Get type value
                    const int type_data = current_item->type_data;

                    // Switch type 0 = INT | 1 CHAR[]
                    switch (type_data)
                    {
                        // INT case
                        case 0:

                            // Check if values match
                            if (*(int *)(current_item->value) == *(int *)(value))                            
                            {
                                // Update counter
                                aiv_decrement_counter(set, index);

                                // Remove item from linked list
                                aiv_list_remove(&(set->hashmap[index].next), &(current_item->list_item));

                                printf("REMOVED! KEY %s WITH VALUE: %d AT INDEX %llu SLOT %llu\n", key,  *(int *)(value), index, i);
                                printf("%d/%d BLOCKS\n", set->counter_list[index], HASHMAP_SIZE_LIST);        

                                return current_item;                            
                            }

                        break;
                        
                        // CHAR case
                        case 1:
                            
                            // Check if values match
                            if ((char *)(current_item->value) == (char *)(value))
                            {
                                // Update counter
                                aiv_decrement_counter(set, index);

                                // Remove item from linked list
                                aiv_list_remove(&(set->hashmap[index].next), &(current_item->list_item));

                                printf("REMOVED! KEY: %s WITH VALUE: %s AT INDEX %llu SLOT %llu\n", key, (char *)(value), index, i);
                                printf("%d/%d BLOCKS\n", set->counter_list[index], HASHMAP_SIZE_LIST);        

                                return current_item;
                            }

                        break;
                    }
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
    printf("PRINT DICTIONARY\n");
    printf("-------------------\n");

    for (size_t i = 0; i < set->capacity; i++)
    {   
        // Check if index node exist
        if (set->hashmap[i].next != NULL)
        {
            printf("ITEMS AT INDEX[%llu]\n", i); 
            aiv_print_list((aiv_set_item*)set->hashmap[i].next);
            printf("-------------------\n");
        }
        else // Index node is empty
        {
            printf("NO ITEMS AT INDEX[%llu]\n", i); 
            printf("-------------------\n");      
        }       
    }

    // Print dictionary stats
    printf("COLLISION: %d/%d\n", set->collision_counter, (*set).capacity/2); 
    printf("CAPACITY: %d\n", set->capacity); 
    printf("-------------------\n");     
}
// -------------------------------------------------------------------------- 