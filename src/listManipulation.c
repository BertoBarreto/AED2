#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <header.h>

/************************
 * Insert Data in lists *
 ************************/
PARTS *InsertPart(PARTS *lst, char *part_num, char *name, char *part_class, int stock)
{
    assert(part_num);
    assert(name);
    assert(part_class);

    PARTS *new_part = (PARTS *)malloc(sizeof(PARTS));

    strcpy(new_part->part_num, part_num);
    strcpy(new_part->name, name);
    strcpy(new_part->class, part_class);
    new_part->stock = stock;
    new_part->next = lst;
    if (new_part->next)
        new_part->next->previous = new_part;
    new_part->previous = NULL;

    return new_part;
}

SETS *InsertSet(SETS *lst, char *set_num, char *name, int year, char *theme)
{
    assert(set_num);
    assert(name);
    assert(theme);

    SETS *new_set = (SETS *)malloc(sizeof(SETS));

    strcpy(new_set->set_num, set_num);
    strcpy(new_set->name, name);
    strcpy(new_set->theme, theme);
    new_set->year = year;

    new_set->next = lst;
    if (new_set->next)
        new_set->next->previous = new_set;
    new_set->previous = NULL;
    return new_set;
}

RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num)
{
    assert(set_num);
    assert(part_num);

    RELATIONS *new_relation = (RELATIONS *)malloc(sizeof(RELATIONS));

    strcpy(new_relation->set_num, set_num);
    strcpy(new_relation->part_num, part_num);
    new_relation->quantity = quantity;
    new_relation->next = lst;
    if (new_relation->next)
        new_relation->next->previous = new_relation;
    new_relation->previous = NULL;

    return new_relation;
}
/*
SETS* Stock_changing(lst *s, int v) {
    SETS *new = (SETS*) malloc(sizeof(SETS));
    new->value = v;
    new->next = s;
    return new;
*/
void OrderSetbyYear(SETS *lst)
{

    int swapped, i;
    SETS *ptr1;
    SETS *lptr = NULL;

    if (lst == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = lst;

        while (ptr1->next != lptr)
        {
            if (ptr1->year > ptr1->next->year)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

char *LowerString(char *string)
{
    char c;
    char *aux = string;
    for (int i = 0; aux[i] != '\0'; i++)
    {
        aux[i] = tolower(aux[i]);
    }
    return aux;
}

int StockParts(PARTS *lst, int counter)
{
    if (lst)
    {
        counter += lst->stock;
        StockParts(lst->next, counter);
    }
    else
        return counter;
}

void swap(SETS *a, SETS *b)
{
    char set_num[100];
    char name[500];
    char theme[500];
    int year;

    strcpy(set_num, a->set_num);
    strcpy(name, a->name);
    strcpy(theme, a->theme);
    year = a->year;

    strcpy(a->set_num, b->set_num);
    strcpy(a->name, b->name);
    strcpy(a->theme, b->theme);
    a->year = b->year;

    strcpy(b->set_num, set_num);
    strcpy(b->name, name);
    strcpy(b->theme, theme);
    b->year = year;
}

SETS *DeleteSetsNode(SETS *node)
{
    SETS *toDelete = node;
    node = toDelete->next;
    free(toDelete);

    return node;
}

SETS *RemoveSetsbyTheme(SETS *lst, const char *theme)
{
    SETS *aux = lst;

    while (aux)
    {
        if (strcmp(LowerString(aux->theme), theme) == 0)
        {                  // aux é o nodo a remover
            if (aux->next) // não último nodo
                aux->next->previous = aux->previous;

            if (aux->previous) // não é o primeiro nodo!
                aux->previous->next = aux->next;
            else                 // é o primeiro nodo
                lst = aux->next; // apenas no caso de ser o 1º

            aux = DeleteSetsNode(aux);
        }
        else
        {
            aux = aux->next;
        }
    }
    return lst;
}

PARTS *DeletePartsNode(PARTS *node)
{
    PARTS *toDelete = node;
    node = toDelete->next;
    free(toDelete);

    return node;
}

PARTS *RemovePartsbyClass(PARTS *lst, const char *class)
{
    PARTS *aux = lst;
    printf("\n%s ", class);
    while (aux)
    {
        if (strcmp(LowerString(aux->class), class) == 0)
        { // aux é o nodo a remover

            if (aux->next) // não último nodo
                aux->next->previous = aux->previous;

            if (aux->previous) // não é o primeiro nodo!
                aux->previous->next = aux->next;
            else                 // é o primeiro nodo
                lst = aux->next; // apenas no caso de ser o 1º

            aux = DeletePartsNode(aux);
        }
        else
        {
            aux = aux->next;
        }
    }
    return lst;
}

int ContPartOccur(RELATIONS *lst, char *part_num)
{
    int count = 0;
    for (; lst; lst = lst->next)
    {
        if (strcmp(lst->part_num, part_num) == 0)
        {
            count += 1;
        }
    }
    return count;
}

PARTS *HighestOccur(PARTS *lst, RELATIONS *rel_lst)
{
    int highest = 0, count = 0;
    PARTS *search = NULL;
    for (; lst; lst = lst->next)
    {
        count = ContPartOccur(rel_lst, lst->part_num);
        if (count > highest)
        {
            highest = count;
            printf("\nHighest: %d", highest);
            search = lst;
        }
    }
    return search;
}