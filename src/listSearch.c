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

int amount(PARTS *lst, int count)
{
    if (lst)
    {
        printf("\n%s", lst->part_num);
        count += 1;
        lst = lst->next;
        printf("next: %s", lst->part_num);
        amount(lst, count);
    }
    else
    {
        return count;
    }
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

    if (parts)
    {

        if (strcmp(part_num, parts->part_num) == 0)
        {
            return parts;
        }

        SearchPartsByNum(parts->next, part_num);
    }
    else
    {
        return NULL;
    }
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
            search = InsertRelation(search, rel->set_num, rel->quantity, rel->part_num);
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
            search = InsertRelation(search, rel->set_num, rel->quantity, rel->part_num);
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
    if (sets)
    {
        if (strcmp(set_num, sets->set_num) == 0)
            return sets;

        sets = sets->next;
        SetsSearchByNum(sets, set_num);
    }
    else
        return NULL;
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

    PARTS *parts_search = NULL;
    if (rel_lst)
    {
        parts_search = SearchPartsByNum(parts_lst, rel_lst->part_num);
        if (parts_search)
        {
            if (rel_lst->next && strcmp(set_num, rel_lst->next->set_num) == 0)
            {
                gotNext = true;
                if (rel_lst->next->quantity > parts_search->stock)
                    return false;
            }
            if (rel_lst->quantity > parts_search->stock)
                return false;
        }

        if (gotNext == true)
            rel_lst = rel_lst->next->next;
        else
            rel_lst = rel_lst->next;

        SearchCanBuildRelations(rel_lst, parts_lst, set_num, false);
    }
    else
        return true;
}

/**
 * @brief This function searches for the sets that can be built with the parts stock.
 * @brief This function firstly will iterate through the sets and get the corresponding relations from a search relation function, then it will check for each relation
 * wich part it is and if the part stock is enough to build the set, then if it is enough it will add that set to the search list and by the end return that list
 * 
 * @param sets_lst ➔ The list of all the sets
 * @param rel_lst ➔ The list of all the relations
 * @param parts_lst ➔ The list of all the parts
 * @param search ➔ The search variable that will receive all the sets that can be built
 * @return SETS* ➔ List of all the sets that can be built
 * @see SearchCanBuildRelations
 * @see SearchRelations
 * @see InsertSet
 */
SETS *SearchSetCanBuild(SETS *sets_lst, RELATIONS *rel_lst, PARTS *parts_lst, SETS *search)
{
    SETS *search_set = NULL;
    RELATIONS *search_rel = NULL;
    if (sets_lst)
    {
        search_rel = SearchRelations(rel_lst, sets_lst->set_num);
        if (search_rel)
        {
            if (SearchCanBuildRelations(search_rel, parts_lst, sets_lst->set_num, false) == true)
            {

                search = InsertSet(search, sets_lst->set_num, sets_lst->name, sets_lst->year, sets_lst->theme);
            }
        }

        SearchSetCanBuild(sets_lst->next, rel_lst, parts_lst, search);
    }
    else
    {
        return search;
    }
}

char *MaxOccurPart(RELATIONS *rel_lst, PARTS *parts_lst)
{
    RELATIONS *aux_rel = NULL;
    PARTS *aux_parts = parts_lst;
    char res[500];
    char *part = res;
    int count = 0, counter = 0, higher = 0;

    for (; aux_parts; aux_parts = aux_parts->next)
    {
        aux_rel = rel_lst->next;
        count = 0;
        while (aux_rel)
        {
            printf("\n%s", aux_rel->part_num);
            if (strcmp(aux_parts->part_num, aux_rel->previous->part_num) == 0)
                count++;
            if (strcmp(aux_parts->part_num, aux_rel->part_num) == 0)
                count++;

            if (aux_rel->next->next)
                aux_rel = aux_rel->next;

            aux_rel = aux_rel->next;
        }
        if (count > higher)
        {
            higher = count;
            printf("\n%s", higher);
            strcpy(res, aux_parts->part_num);
        }
    }
    printf("\n%d", higher);
    printf("\n%s", res);
    return part;
}

char *majority(PARTS *parts, RELATIONS *rel, int higher)
{
    RELATIONS *search_rel = NULL;
    char part_num[500];
    char *part = part_num;
    int count;
    if (parts)
    {
        search_rel = SearchPartsRelations(rel, parts->part_num);
        count = CountOccur(search_rel, 0);
        if (higher < count)
        {
            strcpy(part_num, rel->part_num);
            higher = count;
        }

        majority(parts->next, rel, higher);
    }
    else
    {

        return part;
    }
}

int CountOccur(RELATIONS *rel, int count)
{
    if (rel)
    {
        count += 1;

        return CountOccur(rel->next, count);
    }
    else
        return count;
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
        if (strcmp(set_num, LowerString(lst->set_num)) == 0)
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
/**
 * @brief This function checks if there is any part with a specific part_num.
 * 
 * @param lst ➔ Parts list
 * @param part_num ➔ part_num to check
 * @return true ➔ If finds the part
 * @return false ➔ If doesnt find the part 
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