#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sets.h>
#include <relations.h>

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

SETS *InsertSetsearch(SETS *lst, char *set_num, char *theme, char *name, int year)
{
    SETS *search = malloc(sizeof(SETS));

    strcpy(search->set_num, set_num);
    strcpy(search->theme, theme);
    strcpy(search->name, name);
    search->year = year;

    search->next = lst;
    search->previous = NULL;
    lst = search;

    return lst;
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
    int counter = 0;

    for (; lst; lst = lst->next)
    {
        if (strcmp(theme, LowerString(lst->theme)) == 0)
        {

            search = InsertSetsearch(search, lst->set_num, lst->theme, lst->name, lst->year);
            counter++;
        }
    }

    return search;
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
 * @see InsertSets
 */
SETS *SearchSetCanBuild(SETS *sets_lst, RELATIONS *rel_lst, PARTS *parts_lst, SETS *search)
{
    SETS *search_set = NewSetList();
    RELATIONS *search_rel = NewRelationsList();
    if (sets_lst)
    {
        search_rel = SearchRelations(rel_lst, sets_lst->set_num);
        if (search_rel)
        {
            if (SearchCanBuildRelations(search_rel, parts_lst, sets_lst->set_num, false) == true)
            {

                InsertSets(search, sets_lst->set_num, sets_lst->name, sets_lst->year, sets_lst->theme);
            }
        }

        SearchSetCanBuild(sets_lst->next, rel_lst, parts_lst, search);
    }
    else
    {
        return search;
    }
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
        {
            return true;
        }
    }
    return false;
}