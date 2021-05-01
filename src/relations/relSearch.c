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
 * @brief This function will check if there is enough stock to build the set
 * @brief This function will iterate through a set relations list, and firstly will get the part that the it is checking, 
 * then if that part exists it will check if the quantity needed if higher than the stock of that part
 * if it is, it means that the set cant be built so is better so check if cant be build than if can be 
 * built because it will not check all the parts if one fails saving some time
 * 
 * @param rel_lst ➔ Set Relations list
 * @param parts_lst ➔ Parts list
 * @return true ➔ If the set can be built
 * @return false ➔ If the set cant be built
 */
bool SearchCanBuildRelations(RELATIONS *rel_lst, PARTS *parts_lst, char *set_num, bool gotNext)
{

    PARTS *parts_search = NewPartList();
    for (; rel_lst; rel_lst = rel_lst->next)
    {
        parts_search = SearchPartsByNum(parts_lst, rel_lst->part_num);
        if (parts_search)
        {
            if (rel_lst->quantity > parts_search->stock)
                return false;
        }
    }
    return true;
}