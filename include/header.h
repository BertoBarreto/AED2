#ifndef __HEADER_H__
#define __HEADER_H__
#include "../src/listDefinition.c"
#include <stdbool.h>

/*******************************************
 * Read Files and save their data in lists *
 *******************************************/
PARTS *OpenParts(PARTS *parts);
SETS *OpenSets(SETS *sets);
RELATIONS *OpenRelations(RELATIONS *relations);

/************************
 * Insert Data in lists *
 ************************/
PARTS *InsertPart(PARTS *lst, char *part_num, char *name, char *class, int stock);
SETS *InsertSet(SETS *lst, char *set_num, char *name, int year, char *theme);
RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num);
void OrderSetbyYear(SETS *lst);
char *LowerString(char *string);
int StockParts(PARTS *lst, int counter);
int SetPartsQuantity(RELATIONS *lst, int counter);
void swap(SETS *a, SETS *b);
SETS *DeleteSetsNode(SETS *node);
SETS *RemoveSetsbyTheme(SETS *lst, const char *theme);
PARTS *DeletePartsNode(PARTS *node);
PARTS *RemovePartsbyClass(PARTS *lst, const char *class);

/************************
 * Search data in lists *
 ***********************/
PARTS *SearchPartsByNumClass(PARTS *parts, char *part_num, char *class);
PARTS *PartsSearchByClassAndSet(PARTS *parts, RELATIONS *rel, char *class);
PARTS *PartsSearchBySet(PARTS *parts, RELATIONS *rel);
PARTS *SearchPartsByNum(PARTS *parts, char *part_num);
PARTS *SearchPartsByClass(PARTS *parts, char *class);
RELATIONS *SearchRelations(RELATIONS *rel, char *set_num);
RELATIONS *SearchPartsRelations(RELATIONS *rel, char *part_num);
SETS *SetsSearchByNum(SETS *sets, char *set_num);
SETS *SearchSetbyTheme(SETS *lst, char *theme);
SETS *SearchSetCanBuild(SETS *sets_lst, RELATIONS *rel_lst, PARTS *parts_lst, SETS *search);
bool ExistsClass(PARTS *lst, char *class);
bool ExistsSet(SETS *lst, char *set_num);
bool ExistsTheme(SETS *lst, char *theme);
bool ExistsPart(PARTS *lst, char *part_num);
char *MaxOccurPart(RELATIONS *rel_lst, PARTS *parts_lst);
char *majority(PARTS *parts, RELATIONS *rel, int higher);
int CountOccur(RELATIONS *rel, int count);

/**************************
 * list the Data in lists *
 **************************/
void ListParts(PARTS *lst);
void ListPartsAndRelations(PARTS *lst_parts, RELATIONS *lst_rel);
void ListPartsStock(PARTS *lst);
void ListSets(SETS *lst);
void ListSetsNTY(SETS *lst);
void ListRelations(RELATIONS *lst);

#endif