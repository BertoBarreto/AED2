#ifndef __PARTS_H__
#define __PARTS_H__
#include <stdio.h>
#include <header.h>
/*********************
*    Manipulation    *
*********************/
PARTS *InsertPart(PARTS *lst, const char *part_num, const char *name, const char *part_class, int stock);
PARTS *NewPartList();
int StockParts(PARTS *lst);
int SetPartsQuantity(RELATIONS *lst);
PARTS *DeletePartsNode(PARTS *node);
PARTS *RemovePartsbyClass(PARTS *lst, const char *class);

/*************
*    Show    *
*************/
void ListParts(PARTS *lst);
void ListPartsAndRelations(PARTS *lst_parts, RELATIONS *lst_rel);
void ListPartsStock(PARTS *lst);

/*************
*   Search   *
*************/
PARTS *SearchPartsByNumClass(PARTS *parts, char *part_num, char *class);
PARTS *PartsSearchByClassAndSet(PARTS *parts, RELATIONS *rel, char *class);
PARTS *PartsSearchBySet(PARTS *parts, RELATIONS *rel);
PARTS *SearchPartsByNum(PARTS *parts, char *part_num);
PARTS *SearchPartsByClass(PARTS *parts, char *class);
bool ExistsPart(PARTS *lst, char *part_num);
bool ExistsClass(PARTS *lst, char *class);

#endif