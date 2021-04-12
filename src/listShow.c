#include <header.h>
#include <stdio.h>

void ListParts(PARTS *lst)
{
    if (lst)
    {
        printf("\n%20s - %s", lst->part_num, lst->name);
        ListParts(lst->next);
    }
}

void ListPartsStock(PARTS *lst)
{
    if (lst)
    {
        printf("\n%s - %s - %d", lst->part_num, lst->name, lst->stock);
        ListPartsStock(lst->next);
    }
}

void ListSets(SETS *lst)
{
    if (lst)
    {
        printf("%20s - %d\n", lst->theme, lst->year);
        ListSets(lst->next);
    }
}

void ListSetsNTY(SETS *lst)
{
    if (lst)
    {
        printf("\n%s - %s - %d", lst->name, lst->theme, lst->year);
        ListSetsNTY(lst->next);
    }
}

void ListRelations(RELATIONS *lst)
{
    if (lst)
    {
        printf("%20s - %s\n", lst->set_num, lst->part_num);
        ListRelations(lst->next);
    }
}
