#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <header.h>

/************************
 * Insert Data in lists *
 ************************/
/**   
 * @brief This function allows to insert a part in the parts list, returning the parts list with the new part inserted.
 * @param lst ➔ The parts list where the part is going to be inserted
 * @param part_num ➔ The part_num of the part to insert
 * @param name ➔ The name of the part to insert
 * @param part_class ➔ The class of the part to insert
 * @param stock ➔ The stock of the part to insert
 * @return PARTS* ➔ parts list with the new insertion
 * @see OpenParts
 */
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

SETS *Stock_changing(SETS *lst, char theme)
{
    SETS *new = (SETS *)malloc(sizeof(SETS));
    new->year = 99;
    new->next = lst;
    return new;
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
    SETS *lptr = NULL;

    if (lst == NULL)
        return;

    do
    {
        swapped = 0;
        ptr = lst;

        while (ptr->next != lptr)
        {
            if (ptr->year > ptr->next->year)
            {
                swap(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

/**
 * @brief This function allows to set all the string characters to lower.
 * 
 * @param string 
 * @return char* ➔ LowerString
 */
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

/**
 * @brief This function iterates through the parts list and sums the stock to the counter variable.
 * 
 * @param lst ➔ The parts list
 * @param counter ➔ The variable that sums the stock
 * @return int ➔ The sum of the stock
 */
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

/**
 * @brief This function iterates through the realtions list and sums the part quantity to the counter variable.
 * 
 * @param lst ➔ The relations list
 * @param counter ➔ The variable that sums the quantity
 * @return int ➔ The sum of the quantities
 */
int SetPartsQuantity(RELATIONS *lst, int counter)
{
    if (lst)
    {
        counter += lst->quantity;
        SetPartsQuantity(lst->next, counter);
    }
    else
        return counter;
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
 * @return SETS* 
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
 * @return SETS* 
 */
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

/**
 * @brief This funtion deletes a node from a part list.
 * 
 * @param node ➔ node to delete
 * @return SETS* 
 */
PARTS *DeletePartsNode(PARTS *node)
{
    PARTS *toDelete = node;
    node = toDelete->next;
    free(toDelete);

    return node;
}
/**
 * @brief This function removes all the parts with a specific class.
 * @brief This function iterates through the parts list checking if the actual part class is the same class that the user wants to remove.Then it checks if there is any 
 * part after the actual part and sets the next part previous part to the actual part previous part, then it checks if there is any previous part, and if there is
 * it will set the varible next part from the previous part to the actual part next part. After all of that clutter it deletes the actual node and repeates the cycle.
 * 
 * @param lst ➔ The sets list
 * @param class ➔ The part class to delete
 * @return PARTS* 
 */
PARTS *RemovePartsbyClass(PARTS *lst, const char *class)
{
    PARTS *aux = lst;
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

