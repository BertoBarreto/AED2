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

PARTCOUNTER *InsertCounterSearch(PARTCOUNTER *lst, char *part_num)
{
    if (!lst)
    {
        PARTCOUNTER *counter = malloc(sizeof(PARTCOUNTER));
        strcpy(counter->part_num, part_num);
        counter->counter = 1;
        counter->next = lst;
        lst = counter;
    }
    else if (strcmp(part_num, lst->part_num) == 0)
    {
        lst->counter++;
    }
    else
    {
        lst->next = InsertCounterSearch(lst->next, part_num);
    }
}

char *MoreUsed(PARTCOUNTER *lst)
{
    if (!lst)
        return NULL;

    PARTCOUNTER *max = malloc(sizeof(PARTCOUNTER));
    strcpy(max->part_num, lst->part_num);
    max->counter = lst->counter;

    while (lst->next)
    {
        lst = lst->next;
        if (lst->counter > max->counter)
        {
            strcpy(max->part_num, lst->part_num);
            max->counter = lst->counter;
        }
    }

    char *winner = max->part_num;
    free(max);
    return winner;
}

char *MoreUsedPart(RELATIONS *lst)
{
    PARTCOUNTER *counter = NULL;

    for (; lst; lst = lst->next)
    {
        counter = InsertCounterSearch(counter, lst->part_num);
    }

    char *part = MoreUsed(counter);
    return strdup(part);
}