#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief This function searches parts by part_num and class
 * 
 * @param parts ➔ parts list
 * @param part_num ➔ part_num to search
 * @param class ➔ class to search
 * @return PARTS* ➔ Part found
 */
PARTS *SearchPartsByNumClass(PARTS *parts, char *part_num, char *class)
{
    if (!parts)
        return NULL;
    else if (strcmp(part_num, parts->part_num) == 0)
    {
        if (strcmp(class, LowerString(parts->class)) == 0)
            return parts;
        else
            return NULL;
    }
    else
    {
        return SearchPartsByNumClass(parts->next, part_num, class);
    }
}

/**
 * @brief This function searches for parts with certain class in a relations list.
 * @brief This function iterates through all the relations and searches for all the parts with the part_num and class from the relations
 *  list inserting the parts found in a list and returning the list.
 * 
 * @param parts ➔ Parts list
 * @param rel ➔ Relations list
 * @return PARTS* ➔ List with all the parts found
 */
PARTS *PartsSearchByClassAndSet(PARTS *parts, RELATIONS *rel, char *class)
{
    PARTS *search = NULL;
    PARTS *partSearch = NULL;
    for (; rel; rel = rel->next)
    {
        partSearch = SearchPartsByNumClass(parts, rel->part_num, class);
        if (partSearch)
            search = InsertPart(search, partSearch->part_num, partSearch->name, partSearch->class, partSearch->stock);
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
 * @return PARTS* ➔ Part found 
 */
PARTS *SearchPartsByNum(PARTS *parts, char *part_num)
{

    if (!parts || strcmp(part_num, parts->part_num) == 0)
    {
        return parts;
    }
    else
    {
        return SearchPartsByNum(parts->next, part_num);
    }
}

/**
 * @brief This function searches for a part with a class in the parts list.
 * 
 * @param parts ➔ Parts list
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
 * @brief This function searches for a set by its set_num.
 * 
 * @param sets ➔ Sets list
 * @param set_num ➔ set_num to search for
 * @return SETS* ➔ List of sets found
 */
SETS *SetsSearchByNum(SETS *sets, char *set_num)
{
    if (!sets || set_num == sets->set_num)
    {
        return sets;
    }
    else
    {
        return SetsSearchByNum(sets->next, set_num);
    }
}

/**
 * @brief This function searches for a set by its theme.
 * 
 * @param lst ➔ Sets list
 * @param theme ➔ Theme so search for
 * @return SETS* ➔ List of sets found
 */
SETS *SearchSetbyTheme(SETS *lst, char *theme)
{
    SETS *search = NULL;
    for (; lst; lst = lst->next)
    {
        if (strcmp(theme, LowerString(lst->theme)) == 0)
            search = InsertSet(search, lst->set_num, lst->name, lst->year, lst->theme);
    }
    return search;
}

/**
 * @brief This function checks if a part class exists by iterating by the parts list and if it founds a part with that class then it returns true.
 * 
 * @param lst ➔ Parts list
 * @return true ➔ If finds a part
 * @return false ➔ If doesnt find a part
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

/**
 * @brief This function checks if a set with a specific set_num exists.
 * 
 * @param lst ➔ Sets list
 * @param set_num ➔ set_num to check
 * @return true ➔ If finds a set
 * @return false ➔ If doesnt find a set
 */
bool ExistsSet(SETS *lst, char *set_num)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(set_num, lst->set_num) == 0)
            return true;
    }
    return false;
}

/**
 * @brief This function checks if there is any set with a specific theme.
 * 
 * @param lst ➔ Sets list
 * @param theme ➔ theme to check
 * @return true ➔ If finds a set
 * @return false ➔ If doesnt find a set 
 */
bool ExistsTheme(SETS *lst, char *theme)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(theme, LowerString(lst->theme)) == 0)
            return true;
    }
    return false;
}