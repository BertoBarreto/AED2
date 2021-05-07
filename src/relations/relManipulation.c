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

    if (lst)
        new_relation->next = lst;
    else
        new_relation->next = NULL;

    if (new_relation->next)
        new_relation->next->previous = new_relation;

    new_relation->previous = NULL;
    lst = new_relation;
    //free(new_relation);
    return lst;
}

/**
 * @brief This funtion deletes a node from a relations list.
 * 
 * @param node ➔ node to delete
 * @return Relations* ➔ list without the deleted node
 */
RELATIONS *DeleteRelationsNode(RELATIONS *node)
{
    RELATIONS *toDelete = node;
    node = toDelete->next;
    free(toDelete);

    return node;
}

/**
 * @brief This function removes all the relations with a specific theme.
 * @brief This function iterates through the relations list checking if the actual set is the same set as the one to remove.Then it checks if there is any 
 * realtion after the actual relation and sets the next relation previous relation to the actual relation previous relation, then it checks if there is any previous relation and if there is
 * it will set the varible next relation from the previous relation to the actual relation next relation. After all of that clutter it deletes the actual node and repeates the cycle.
 * 
 * @param lst ➔ The realtions list
 * @param theme ➔ The set to delete
 * @return Relations* ➔ List with relations removed
 * @see LowerString
 * @see DeleteSetsNode
 */
RELATIONS *RemoveRelationsbySet(RELATIONS *lst, const char *set_num)
{
    RELATIONS *aux = lst;
    bool found = false;

    while (aux)
    {
        if (found = true)
        {
            if (strcmp(aux->next->set_num, set_num) != 0)
            {
                return lst;
            }
        }
        if (strcmp(LowerString(aux->set_num), set_num) == 0)
        {

            if (aux->next)
                aux->next->previous = aux->previous;

            if (aux->previous)
                aux->previous->next = aux->next;
            else
                lst = aux->next;

            aux = DeleteRelationsNode(aux);
            found = true;
        }
        else
        {
            aux = aux->next;
        }
    }
    return lst;
}


void FreeRelations(RELATIONS *lst)
{

    while (lst)
    {
        RELATIONS *next = lst->next;
        free(lst);
        lst = next;
    }
}