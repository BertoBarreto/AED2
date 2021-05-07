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
    PARTS *new_part = malloc(sizeof(PARTS));

    strcpy(new_part->part_num, part_num);
    strcpy(new_part->name, name);
    strcpy(new_part->class, part_class);
    new_part->stock = stock;

    if (lst)
        new_part->next = lst;
    else
        new_part->next = NULL;

    if (new_part->next)
        new_part->next->previous = new_part;

    new_part->previous = NULL;
    lst = new_part;

    return lst;
}

/**
 * @brief This function iterates through the parts list and sums the stock to the counter variable.
 * 
 * @param lst ➔ The parts list
 * @param counter ➔ The variable that sums the stock
 * @return int ➔ The sum of the stock
 */
int StockParts(PARTS *lst)
{
    int counter = 0;
    for (; lst; lst = lst->next)
    {
        counter += lst->stock;
    }
    return counter;
}

/**
 * @brief This function iterates through the realtions list and sums the part quantity to the counter variable.
 * 
 * @param lst ➔ The relations list
 * @param counter ➔ The variable that sums the quantity
 * @return int ➔ The sum of the quantities
 */
int SetPartsQuantity(RELATIONS *lst)
{
    int counter = 0;
    for (; lst; lst = lst->next)
    {
        counter += lst->quantity;
    }
    return counter;
}

/**
 * @brief This funtion deletes a node from a part list.
 * 
 * @param node ➔ node to delete
 * @return PARTS* ➔ List without the deleted node
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
 * @return PARTS* ➔ New list without the parts removed
 * @see LowerString
 */
PARTS *RemovePartsbyClass(PARTS *lst, const char *class)
{
    PARTS *aux = lst;
    while (aux)
    {
        if (strcmp(LowerString(aux->class), class) == 0)
        {

            if (aux->next)
                aux->next->previous = aux->previous;

            if (aux->previous)
                aux->previous->next = aux->next;
            else
                lst = aux->next;

            aux = DeletePartsNode(aux);
        }
        else
        {
            aux = aux->next;
        }
    }
    return lst;
}

/**
 * @brief This function allow to edit the stock of a part, if the quantity if negative it will decrease the stock,
 * if it his positive then it will increase
 * 
 * @param lst ➔ List of parts
 * @param part_num ➔ Part_num of the part to change stock
 * @param quantity ➔ Quantity of stock to add or remove
 */
void EditPartStock(PARTS *lst, char *part_num, int quantity)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(lst->part_num, part_num) == 0)
        {
            if (lst->stock + quantity >= 0)
                lst->stock += quantity;
            else
                printf("\nThere isn't enought stock to remove that quantity");
        }
    }
}

void FreeParts(PARTS *lst)
{
    while (lst)
    {
        PARTS *next = lst->next;
        free(lst);
        lst = next;
    }
}