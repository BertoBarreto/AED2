#include <header.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

SETS *SearchSetbyTheme(SETS *lst, char *theme)
{
    SETS *search = NULL;
    char set_theme[500];
    for (; lst; lst = lst->next)
    {
        if (strcmp(theme, LowerString(lst->theme)) == 0)
        {
            search = InsertSet(search, lst->set_num, lst->name, lst->year, lst->theme);
        }
    }
    return search;
}

bool ExistsClass(PARTS *lst, char *class)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(class, LowerString(lst->class)) == 0)
            return true;
    }
    return false;
}

bool ExistsSet(SETS *lst, char *set_num)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(set_num, lst->set_num) == 0)
            return true;
    }
    return false;
}

bool ExistsTheme(SETS *lst, char *theme)
{
    for (; lst; lst = lst->next)
    {
        if (strcmp(theme, LowerString(lst->theme)) == 0)
            return true;
    }
    return false;
}