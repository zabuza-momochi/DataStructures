// Dictionaries Challenge
// ● They are unique sets with a value
// ● Implement them over the set structures to support any kind of value
// ● Higher Level Exercise: keep count of how many collisions are in the hash
// map and increase the size of the hash table when there is too much
// ‘pressure’ (note: it requires rehashing of the whole dictionary)

// Include Header -----------------------------------------------------------
#include "dictionary.h"
// --------------------------------------------------------------------------

// Entry point -------------------------------------------------------------- 
int main(int argc, char **argv)
{
    // Declaration
    struct aiv_set my_dict;
    
    // Init
    aiv_set_init(&my_dict, HASHMAP_SIZE_DEFAULT);
    
    // Insert item
    aiv_set_insert(&my_dict, "Hello", (void *)&(int){10}, 0);
    aiv_set_insert(&my_dict, "Test",  (void *)&(int){20}, 0);
    aiv_set_insert(&my_dict, "Never", (void *)&(int){30}, 0);
    aiv_set_insert(&my_dict, "Pippo", (void *)&(int){20}, 0);
    aiv_set_insert(&my_dict, "Ciao",  (void *)"Mondo", 1);
    
    // Print dictionary
    printf("-----------------------------------------------------\n");
    aiv_set_print(&my_dict);

    // Find item
    printf("TRY FIND ITEM \n");
    aiv_set_find(&my_dict, "Ciao", "Mondo");
    
    // Remove item
    printf("-----------------------------------------------------\n");
    printf("TRY REMOVE ITEM \n");
    aiv_set_remove(&my_dict, "Test", (void *)&(int){20});
    
    printf("-----------------------------------------------------\n");
    printf("TRY REMOVE ITEM \n");
    aiv_set_remove(&my_dict, "Never", (void *)&(int){30});
    
    // Print dictionary
    printf("-----------------------------------------------------\n");
    aiv_set_print(&my_dict);

    // Insert
    aiv_set_insert(&my_dict, "Hello", (void *)"Universe", 1);
    aiv_set_insert(&my_dict, "Spank", (void *)&(int){5}, 0);
    aiv_set_insert(&my_dict, "Power", (void *)"Max", 1);
    
    // Print dictionary
    printf("-----------------------------------------------------\n");
    aiv_set_print(&my_dict);

    // Insert item
    aiv_set_insert(&my_dict, "Pluto", (void *)"Paperino", 1);

    // Print dictionary
    printf("-----------------------------------------------------\n");
    aiv_set_print(&my_dict);

    // End of program
    printf("\nEND -------------------------------------------------\n");

    return 0;
}
// -------------------------------------------------------------------------- 
