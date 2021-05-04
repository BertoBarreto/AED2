#include <header.h>
#include <stdio.h>
#include <string.h>
#include <parts.h>

/**
 * @brief This function iterates through the parts list, printing part_num and name.
 * part_num - name
 * 
 * @param lst ➔ Parts list to show
 */
void ListParts(PARTS *lst)
{
    PARTS *aux = lst->next;
    printf("\nPart_num    Name  Class   Stock   Quantity");
    for (; aux != lst; aux = aux->next)
    {
        printf("\n%s - %s - %s - %d - %d", aux->part_num, aux->name, aux->class, aux->stock);
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
