#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <header.h>
#include <relations.h>
#include <sets.h>

/**   
 * @brief This function allows to insert a set in the sets list, returning the sets list with the new set inserted.
 * @param lst ➔ The sets list where the set is going to be inserted
 * @param set_num ➔ The set_num of the set to insert
 * @param name ➔ The name of the set to insert
 * @param year ➔ The year of the set to insert
 * @param theme ➔ The theme of the set to insert
 * @return SETS* ➔ sets list with the new insertion
 * @see OpenSets
 */
SETS *InsertSets(SETS *lst, char *set_num, char *name, int year, char *theme)
{
    assert(set_num);
    assert(name);
    assert(theme);

    SETS *new_set = malloc(sizeof(SETS));

    strcpy(new_set->set_num, set_num);
    strcpy(new_set->name, name);
    strcpy(new_set->theme, theme);
    new_set->year = year;

    if (lst)
        new_set->next = lst;
    else
        new_set->next = NULL;

    if (new_set->next)
        new_set->next->previous = new_set;

    new_set->previous = NULL;
    lst = new_set;

    return lst;
}

/**   
 * @brief This function allows to Order a set by its year acendant.
 * @brief This function firts stores the list in another list, then it enters a do while cycle that checks if anything has been changed(its stored in the swapped variable) 
 * and resets the swapped variable and the list so that its starts again in the list.Inside the do while there is a while cicly that iterates through the list while the next 
 * position year is diferent from the last position year, if the condition is true then it will check if in the next position the year is higher then in the current position 
 * and if it is it will swap the two of them and set the swapped to 1, after that it will store the last set in an auxiliar variable and in the next iteration start 
 * the swapped at 0 to reset the varible and the list pointer.
 * @param lst ➔ The sets list to be ordered
 */
void OrderSetbyYear(SETS *lst)
{

    int swapped;
    SETS *ptr = NULL;

    if (!lst)
        return;

    do
    {

        swapped = 0;
        ptr = lst;

        while (ptr->next)
        {
            if (ptr->year > ptr->next->year)
            {
                swap(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
    } while (swapped == 1);
}

/**
 * @brief This function swaps the set a for the set b swapping their values aswell.
 * 
 * @param a ➔ The first set
 * @param b ➔ The seond set
 */
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

/**
 * @brief This funtion deletes a node from a sets list.
 * 
 * @param node ➔ node to delete
 * @return SETS* ➔ list without the deleted node
 */
SETS *DeleteSetsNode(SETS *node)
{
    SETS *toDelete = node;
    node = toDelete->next;
    free(toDelete);

    return node;
}

/**
 * @brief This function removes all the sets with a specific theme.
 * @brief This function iterates through the sets list checking if the actual set theme is the same theme that the user wants to remove.Then it checks if there is any 
 * set after the actual set and sets the next set previous set to the actual set previous set, then it checks if there is any previous set and if there is
 * it will set the varible next set from the previous set to the actual set next set. After all of that clutter it deletes the actual node and repeates the cycle.
 * 
 * @param lst ➔ The sets list
 * @param theme ➔ The set theme to delete
 * @return SETS* ➔ List with sets removed
 * @see LowerString
 * @see DeleteSetsNode
 */
SETS *RemoveSetsbyTheme(SETS *lst, RELATIONS *rel_lst, const char *theme)
{
    SETS *aux = lst;

    while (aux)
    {
        if (strcmp(LowerString(aux->theme), theme) == 0)
        {
            if (aux->next)
                aux->next->previous = aux->previous;

            if (aux->previous)
                aux->previous->next = aux->next;
            else
                lst = aux->next;

            rel_lst = RemoveRelationsbySet(rel_lst, LowerString(aux->set_num));

            aux = DeleteSetsNode(aux);
        }
        else
        {
            aux = aux->next;
        }
    }
    return lst;
}

void FreeSets(SETS *lst)
{
    while (lst)
    {
        SETS *next = lst->next;
        free(lst);
        lst = next;
    }
}