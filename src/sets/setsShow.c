#include <header.h>
#include <stdio.h>
#include <string.h>
#include <sets.h>

/**
 * @brief This function iterates through the sets list, printing theme and year.
 * theme - year
 * 
 * @param lst ➔ Sets list to show
 */
void ListSets(SETS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("%20s - %20s - %d\n", lst->set_num, lst->theme, lst->year);
    }
}

/**
 * @brief This function iterates through the sets list, printing name, theme, year.
 * name - theme - year
 * 
 * @param lst ➔ Sets list to show
 */
void ListSetsNTY(SETS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("\n%s - %s - %d", lst->name, lst->theme, lst->year);
    }
}
