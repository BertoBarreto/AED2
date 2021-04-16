#include <header.h>
#include <stdio.h>

void ListParts(PARTS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("\n%20s - %s", lst->part_num, lst->name);
    }
}

void ListPartsStock(PARTS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("\n%s - %s - %d", lst->part_num, lst->name, lst->stock);
    }
}

void ListSets(SETS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("%20s - %d\n", lst->theme, lst->year);
    }
}

void ListSetsNTY(SETS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("\n%s - %s - %d", lst->name, lst->theme, lst->year);
    }
}

void ListRelations(RELATIONS *lst)
{
    for (; lst; lst = lst->next)
    {
        printf("%20s - %s\n", lst->set_num, lst->part_num);
    }
}
