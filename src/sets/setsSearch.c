#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sets.h>
#include <parts.h>

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
    int counter = 0;

    for (; lst; lst = lst->next)
    {
        if (strcmp(theme, LowerString(lst->theme)) == 0)
        {

            search = InsertSets(search, lst->set_num, lst->name, lst->year, lst->theme);
            counter++;
        }
    }

    return search;
}

/**
 * @brief This function allows to search for sets that can be built
 * @brief This function iterates through the relations list, verifing if the set_num of the actual
 *  position in the list is diferent from the previous because if it is it means that we are in another set so 
 * we need to check if the boolean canBuild is true, if it is then the set will be added to the list of sets that can be built.
 * if the condition isnt verified then the part of the actual position will bve searched and check if the stock of that part is lower then the needed quantity
 * and if that verifies then the bool canBuild will be setted to false so that when we change set the set that cant be built isnt added to the sets that can be built list
 * @param sets_lst ➔ The sets list
 * @param rel_lst ➔ The relations list
 * @param parts_lst ➔ The parts list
 * @return SETS* ➔ List of all the sets that can be built
 * @see SetsSearchByNum
 * @see InsertSets
 * @see SearchPartsByNum
 */
SETS *SearchSetCanBuild(SETS *sets_lst, RELATIONS *rel_lst, PARTS *parts_lst)
{
    SETS *search = NULL;
    SETS *set = NULL;
    PARTS *part = NULL;
    bool canBuild = true;

    for (; rel_lst; rel_lst = rel_lst->next)
    {

        if (rel_lst->previous)
        {

            if (strcmp(rel_lst->previous->set_num, rel_lst->set_num) != 0)
            {

                if (canBuild == true)
                {

                    set = SetsSearchByNum(sets_lst, rel_lst->previous->set_num);

                    if (set)
                        search = InsertSets(search, set->set_num, set->name, set->year, set->theme);
                }
                canBuild = true;
            }
        }
        if (canBuild == true)
        {

            part = SearchPartsByNum(parts_lst, rel_lst->part_num);
            if (part)
            {

                if (part->stock < rel_lst->quantity)
                    canBuild = false;
            }
            else
            {
                canBuild = false;
            }
        }
    }

    return search;
}

/**
 * @brief This function checks if a set with a specific set_num exists.
 * 
 * @param lst ➔ Sets list
 * @param set_num ➔ set_num to check
 * @return true ➔ If finds a set
 * @return false ➔ If doesnt find a set
 * @see LowerString
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
 * @see LowerString
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