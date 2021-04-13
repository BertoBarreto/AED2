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
void swap(SETS *a, SETS *b);
char *LowerString(char *string);
void OrderSetbyYear(SETS *lst);
int StockParts(PARTS *lst, int counter);
SETS *DeleteSetsNode(SETS *node);
SETS *RemoveSetsbyTheme(SETS *lst, const char *theme);

/************************
 * Search data in lists *
 ***********************/
PARTS *PartsSearchByClassAndSet(PARTS *parts, RELATIONS *rel, char *class);
PARTS *SearchPartsByNumClass(PARTS *parts, char *part_num, char *class);
PARTS *SearchPartsByNum(PARTS *parts, char *part_num);
PARTS *SearchPartsByClass(PARTS *parts, char *class);
RELATIONS *SearchRelations(RELATIONS *rel, char *set_num);
SETS *SetsSearchByNum(SETS *sets, char *set_num);
SETS *SearchSetbyTheme(SETS *lst, char *theme);
PARTS *PartsSearchBySet(PARTS *parts, RELATIONS *rel);
bool ExistsClass(PARTS *lst, char *class);
bool ExistsSet(SETS *lst, char *set_num);
bool ExistsTheme(SETS *lst, char *theme);

/**************************
 * list the Data in lists *
 **************************/
void ListParts(PARTS *lst);
void ListPartsStock(PARTS *lst);
void ListSets(SETS *lst);
void ListSetsNTY(SETS *lst);
void ListRelations(RELATIONS *lst);

#endif