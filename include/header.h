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
char *LowerString(char *string);

#endif