#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _part_counter
{
    char part_num[500];
    int counter;
    struct _part_counter *next;
} PARTCOUNTER;

PARTCOUNTER *NewCounter(PARTCOUNTER *lst, char *part_num)
{
    PARTCOUNTER *counter = malloc(sizeof(PARTCOUNTER));
    strcpy(counter->part_num, part_num);
    counter->counter = 1;
    counter->next = NULL;
}

PARTCOUNTER *count_part(PARTCOUNTER *lst, char *part_num)
{
    if (!lst)
    {
        lst = NewCounter(lst, part_num);
    }
    else
    {
        while (lst)
        {
            if (strcmp(part_num, lst->part_num) == 0)
            {
                lst->counter++;
            }
        }
    }
    return lst;
}

char *more_used(PARTCOUNTER *lst)
{
    if (!lst)
        return NULL;

    PARTCOUNTER *max = malloc(sizeof(PARTCOUNTER));
    max->counter = lst->counter;
    strcpy(max->part_num, lst->part_num);

    while (lst->next)
    {
        lst = lst->next; // <=== incremento
        if (lst->counter > max->counter)
        {
            max->counter = lst->counter;
            strcpy(max->part_num, lst->part_num);
        }
    }

    char *winner = max->part_num;
    free(max);
    return winner;
}
PARTS *MaxOccurPart(RELATIONS *guard)
{
    PARTCOUNTER *counter = NULL;
}

char *marca_mais_usada(RELATIONS *guard)
{
    PARTCOUNTER *counter = NULL;

    RELATIONS *rel = guard->next;
    while (rel != guard)
    {
        counter = count_part(counter, rel->part_num);
        rel = rel->next;
    }

    char *part = more_used(counter);
    //libertar_marcas(counter);
    return strdup(part);
}
