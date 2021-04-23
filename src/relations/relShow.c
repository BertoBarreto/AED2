#include <header.h>
#include <stdio.h>
#include <string.h>
#include <relations.h>

/**
 * @brief This function iterates through the Relations list, printing set_num and part_num.
 * set_num - part_num
 * 
 * @param lst ➔ Sets list to show
 */
void ListRelations(RELATIONS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("%20s - %s\n", lst->set_num, lst->part_num);
    }
}