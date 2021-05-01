#ifndef __RELATIONS_H__
#define __RELATIONS_H__
#include <stdio.h>
#include <header.h>

/*********************
*    Manipulation    *
*********************/
RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num);
RELATIONS *NewRelationsList();
/*************
*    Show    *
*************/
void ListRelations(RELATIONS *lst);
/*************
*   Search   *
*************/
RELATIONS *SearchRelations(RELATIONS *rel, char *set_num);
RELATIONS *SearchPartsRelations(RELATIONS *rel, char *part_num);
bool SearchCanBuildRelations(RELATIONS *rel_lst, PARTS *parts_lst, char *set_num, bool gotNext);
char *MoreUsedPart(RELATIONS *lst);

#endif