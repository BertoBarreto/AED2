#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <relations.h>
#include <parts.h>

/**
 * @brief This function searches for all the relations with a set_num.
 * 
 * @param rel ➔ Relations list
 * @param set_num ➔ The set_num to search for
 * @return RELATIONS* ➔ List of relations found
 * @see InsertRelation
 */
RELATIONS *SearchRelations(RELATIONS *rel, char *set_num)
{
    RELATIONS *search = NULL;

    for (; rel; rel = rel->next)
    {
        if (strcmp(set_num, rel->set_num) == 0)
        {
            search = InsertRelation(search, rel->set_num, rel->quantity, rel->part_num);
        }
    }
    return search;
}

/**
 * @brief This function searches for all the relations with a set_num.
 * 
 * @param rel ➔ Relations list
 * @param set_num ➔ The set_num to search for
 * @return RELATIONS* ➔ List of relations found
 * @see InsertRelation
 */
RELATIONS *SearchPartsRelations(RELATIONS *rel, char *part_num)
{
    RELATIONS *search = NULL;

    for (; rel; rel = rel->next)
    {
        if (strcmp(part_num, rel->part_num) == 0)
            InsertRelation(search, rel->set_num, rel->quantity, rel->part_num);
    }
    return search;
}

/**
 * @brief List of parts to be counted 
 */
typedef struct _part_counter
{
    char part_num[500];
    int counter;
    struct _part_counter *next;
} PARTCOUNTER;

/**
 * @brief This function allows to inset a part into the PARTCOUNTER list, it checks if the list has values in the actual positon, if not then 
 * it will add the new part with counter to 1, else if the part that is in the actual position is the same that we are trying to insert then
 * the counter of that part will be increased, if none of those conditions verifies then it will check the next position
 * 
 * @param lst ➔ PARTCOUNTER list
 * @param part_num ➔ Part to count
 * @return PARTCOUNTER* ➔ List with the new counter
 */
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
        lst->next = InsertCounterSearch(lst, part_num);
    }

    return lst;
}

/**
 * @brief This function finds the part that has the higher counter in the list PARTCOUNTER iterating through the list 
 * and storing the values that are higher than the actual higher counter.
 * 
 * @param lst ➔ List PARTCOUNTER
 * @return char* ➔ More used part
 */
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

/**
 * @brief This function Iterates though the realations list calling the insert counter function so that it counts the parts in the realations list
 * the it calls the MoreUsed function storing the part_num that it returns in a string and returning it 
 * 
 * @param lst ➔ Realations list
 * @return char* ➔ More used part in the realations list
 * @see InsertCounterSearch
 * @see MoreUsed
 */
char *MoreUsedPart(RELATIONS *lst)
{
    PARTCOUNTER *counter = NULL;

    for (; lst; lst = lst->next)
    {
        counter = InsertCounterSearch(counter, lst->part_num);
    }
    printf("\nHere");
    char *part = MoreUsed(counter);

    return strdup(part);
}