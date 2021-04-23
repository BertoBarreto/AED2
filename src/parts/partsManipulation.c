#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <header.h>
#include <parts.h>

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
PARTS *InsertPart(PARTS *lst, const char *part_num, const char *name, const char *part_class, int stock)
{
    assert(lst);

    PARTS *new_part = malloc(sizeof(PARTS));
    assert(new_part);

    strcpy(new_part->part_num, part_num);
    strcpy(new_part->name, name);
    strcpy(new_part->class, part_class);
    new_part->stock = stock;
    new_part->next = lst;

    new_part->next = NULL;
    new_part->previous = lst;
    if (new_part->previous)
        new_part->previous->next = new_part;
    return new_part;
}

/**
 * @brief This function initializes the parts list, setting everything to null
 * 
 * @return PARTS* ➔ list
 */
PARTS *NewPartList()
{
    PARTS *guard = malloc(sizeof(PARTS));
    assert(guard);
    guard->part_num[0] = '\0';
    guard->name[0] = '\0';
    guard->class[0] = '\0';
    guard->stock = 0;

    guard->previous = guard->next = guard;
    return guard;
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