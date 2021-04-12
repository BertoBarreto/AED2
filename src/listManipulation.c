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
    assert(new_part);

    strcpy(new_part->part_num, part_num);
    strcpy(new_part->name, name);
    strcpy(new_part->class, part_class);
    new_part->stock = stock;
    new_part->next = lst;

    return new_part;
}

SETS *InsertSet(SETS *lst, char *set_num, char *name, int year, char *theme)
{
    assert(set_num);
    assert(name);
    assert(theme);

    SETS *new_set = (SETS *)malloc(sizeof(SETS));
    assert(new_set);

    strcpy(new_set->set_num, set_num);
    strcpy(new_set->name, name);
    strcpy(new_set->theme, theme);
    new_set->year = year;
    new_set->next = lst;

    return new_set;
}

RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num)
{
    assert(set_num);
    assert(part_num);

    RELATIONS *new_relation = (RELATIONS *)malloc(sizeof(RELATIONS));
    assert(new_relation);

    strcpy(new_relation->set_num, set_num);
    strcpy(new_relation->part_num, part_num);
    new_relation->quantity = quantity;
    new_relation->next = lst;

    return new_relation;
}

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

void LowerString(char *string)
{
    char c;
    for (int i = 0; string[i] != '\0'; i++)
    {
        string[i] = tolower(string[i]);
    }
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

void RemoveSetsbyTheme(SETS *lst, const char *theme)
{
    if (theme && lst)
    {
        for (; lst; lst = lst->next)
        {

            if (strcmp(lst->theme, theme) == 0)
            {
                SETS *next = lst->next;
                free(lst->theme);
                free(lst->name);
                free(lst->set_num);
                free(lst);
            }
        }
    }
    else
    {
        return;
    }
}