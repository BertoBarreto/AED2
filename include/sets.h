#ifndef __SETS_H__
#define __SETS_H__
#include <stdio.h>
#include <header.h>
/*********************
*    Manipulation    *
*********************/
SETS *InsertSets(SETS *lst, char *set_num, char *name, int year, char *theme);
SETS *NewSetList();
void OrderSetbyYear(SETS *lst);
void swap(SETS *a, SETS *b);
SETS *DeleteSetsNode(SETS *node);
SETS *RemoveSetsbyTheme(SETS *lst, const char *theme);

/*************
*    Show    *
*************/
void ListSets(SETS *lst);
void ListSetsNTY(SETS *lst);
/*************
*   Search   *
*************/
SETS *SetsSearchByNum(SETS *sets, char *set_num);
SETS *InsertSetsearch(SETS *lst, char *set_num, char *theme, char *name, int year);
SETS *SearchSetbyTheme(SETS *lst, char *theme);
SETS *SearchSetCanBuild(SETS *sets_lst, RELATIONS *rel_lst, PARTS *parts_lst);
bool ExistsSet(SETS *lst, char *set_num);
bool ExistsTheme(SETS *lst, char *theme);

#endif