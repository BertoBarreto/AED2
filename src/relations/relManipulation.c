#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <header.h>
#include <relations.h>

/**   
 * @brief This function allows to insert a set to parts relation in the relations list, returning the relations list with the new realtion inserted.
 * @param lst ➔ The sets list where the set is going to be inserted
 * @param set_num ➔ The set_num of the set to insert in the relation
 * @param quantity ➔ The quantity of the part to insert in the relation
 * @param part_num ➔ The  of the set to insert
 * @param theme ➔ The theme of the set to insert
 * @return RELATIONS* ➔ relations list with the new insertion
 * @see OpenRelations
 */
RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num)
{
    assert(set_num);
    assert(part_num);

    RELATIONS *new_relation = malloc(sizeof(RELATIONS));

    strcpy(new_relation->set_num, set_num);
    strcpy(new_relation->part_num, part_num);
    new_relation->quantity = quantity;
    new_relation->next = NULL;
    new_relation->previous = lst;

    if (new_relation->next)
        new_relation->next->previous = new_relation;
    if (new_relation->previous)
        new_relation->previous->next = new_relation;

    return new_relation;
}

/**
 * @brief This function initializes the relations list, setting everything to null
 * 
 * @return RELATIONS* ➔ list
 */
RELATIONS *NewRelationsList()
{
    RELATIONS *guard = malloc(sizeof(RELATIONS));
    assert(guard);
    guard->set_num[0] = '\0';
    guard->part_num[0] = '\0';
    guard->quantity = '\0';

    guard->previous = guard->next = guard;
    return guard;
}