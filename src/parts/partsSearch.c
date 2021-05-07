#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parts.h>
#include <relations.h>

/**
 * @brief This function searches parts by part_num and class
 * 
 * @param parts ➔ parts list
 * @param part_num ➔ part_num to search
 * @param class ➔ class to search
 * @return PARTS* ➔ Part found
 * @see LowerString
 */
PARTS *SearchPartsByNumClass(PARTS *parts, char *part_num, char *class)
{
    for (; parts; parts = parts->next)
    {
        if (strcmp(part_num, parts->part_num) == 0)
        {
            if (strcmp(class, LowerString(parts->class)) == 0)
                return parts;
        }
    }
    return NULL;
}

/**
 * @brief This function searches for parts with certain class in a relations list.
 * @brief This function iterates through all the relations and searches for all the parts with the part_num and class from the relations
 *  list inserting the parts found in a list and returning the list.
 * 
 * @param parts ➔ Parts list
 * @param rel ➔ Relations list
 * @return PARTS* ➔ List with all the parts found
 * @see SearchPartsByNumClass
 * @see InsertPart
 */
PARTS *PartsSearchByClassAndSet(PARTS *parts, RELATIONS *rel, char *class)
{
    PARTS *search = NULL;
    PARTS *partSearch = NULL;
    for (; rel; rel = rel->next)
    {
        partSearch = SearchPartsByNumClass(parts, rel->part_num, class);
        if (partSearch)
        {

            search = InsertPart(search, partSearch->part_num, partSearch->name, partSearch->class, partSearch->stock);
        }
    }
    return search;
}

/**
 * @brief This function searches for all the parts in a set. 
 * @brief This function iterates through all the relations and searches for all the parts with the part_num from the relations
 *  list inserting the parts found in a list and returning the list.
 * 
 * @param parts ➔ Parts list
 * @param rel ➔ Relations list
 * @return PARTS* ➔ List with all the parts found
 * @see SearchPartsByNum
 * @see InsertPart
 */
PARTS *PartsSearchBySet(PARTS *parts, RELATIONS *rel)
{
    PARTS *search = NULL;
    PARTS *partSearch = NULL;
    for (; rel; rel = rel->next)
    {
        partSearch = SearchPartsByNum(parts, rel->part_num);
        if (partSearch)
            search = InsertPart(search, partSearch->part_num, partSearch->name, partSearch->class, partSearch->stock);
    }
    return search;
}

/**
 * @brief This function searches for a part with a part_num in the parts list.
 * 
 * @param parts ➔ Parts list
 * @param part_num ➔ part_num to search
 * @return PARTS* ➔ Part found 
 */
PARTS *SearchPartsByNum(PARTS *parts, char *part_num)
{
    PARTS *aux = parts;
    for (; aux; aux = aux->next)
    {

        if (strcmp(part_num, aux->part_num) == 0)
        {
            return aux;
        }
    }
    return NULL;
}

/**
 * @brief This function searches for a part with a class in the parts list.
 * 
 * @param parts ➔ Parts list
 * @param class ➔ Class to search
 * @return PARTS* ➔ Part found  
 */
PARTS *SearchPartsByClass(PARTS *parts, char *class)
{

    if (!parts || strcmp(class, parts->class) == 0)
    {
        return parts;
    }
    else
    {
        return SearchPartsByClass(parts->next, class);
    }
}

/**
 * @brief This function checks if there is any part with a specific part_num.
 * 
 * @param lst ➔ Parts list
 * @param part_num ➔ part_num to check
 * @return true ➔ If finds the part
 * @return false ➔ If doesnt find the part
 * @see LowerString 
 */
bool ExistsPart(PARTS *lst, char *part_num)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(part_num, LowerString(lst->part_num)) == 0)
            return true;
    }
    return false;
}

/**
 * @brief This function checks if a part class exists by iterating by the parts list and if it founds a part with that class then it returns true.
 * 
 * @param lst ➔ Parts list
 * @return true ➔ If finds a part
 * @return false ➔ If doesnt find a part
 * @see LowerString
 */
bool ExistsClass(PARTS *lst, char *class)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(class, LowerString(lst->class)) == 0)
            return true;
    }
    return false;
}