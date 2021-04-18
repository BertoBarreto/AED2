#include <header.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief This function iterates through the parts list, printing part_num and name.
 * part_num - name
 * 
 * @param lst ➔ Parts list to show
 */
void ListParts(PARTS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("\n%20s - %s", lst->part_num, lst->name);
    }
}

/**
 * @brief This function iterates through the parts and relations list, printing all the information
 * from the part and the quantity from the relation.
 * part_num - name - class - stock - quantity
 * 
 * @param lst_parts ➔ Parts list to show
 * @param lst_rel ➔ Relations list to show
 */
void ListPartsAndRelations(PARTS *lst_parts, RELATIONS *lst_rel)
{
    PARTS *aux_parts = lst_parts;
    for (; lst_rel; lst_rel = lst_rel->next)
    {

        for (; aux_parts; aux_parts = aux_parts->next)
        {
            if (strcmp(lst_rel->part_num, aux_parts->part_num) == 0)
                printf("\n%s - %s - %s - %d - %d", aux_parts->part_num, aux_parts->name, aux_parts->class, aux_parts->stock, lst_rel->quantity);
        }
        aux_parts = lst_parts;
    }
}

/**
 * @brief This function iterates through the parts list, printing part_num and name.
 * part_num - name - stock
 * 
 * @param lst ➔ Parts list to show
 */
void ListPartsStock(PARTS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("\n%s - %s - %d", lst->part_num, lst->name, lst->stock);
    }
}

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
        printf("%20s - %d\n", lst->theme, lst->year);
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
