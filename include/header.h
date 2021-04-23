#ifndef __HEADER_H__
#define __HEADER_H__
#include "../src/listDefinition.c"
#include <stdbool.h>

/*******************************************
 * Read Files and save their data in lists *
 *******************************************/
void OpenParts(PARTS *parts);
void OpenSets(SETS *sets);
void OpenRelations(RELATIONS *relations);

/************************
 * Insert Data in lists *
 ************************/
char *LowerString(char *string);

#endif