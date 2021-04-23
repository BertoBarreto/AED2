#include <stdio.h>
#include <string.h>
#include <header.h>

SETS *Stock_changing(SETS *lst, char theme)
{
    SETS *new = (SETS *)malloc(sizeof(SETS));
    new->year = 99;
    new->next = lst;
    return new;
}

/**
 * @brief This function allows to set all the string characters to lower.
 * 
 * @param string 
 * @return char* ➔ LowerString
 */
char *LowerString(char *string)
{
    char c;
    char *aux = string;
    for (int i = 0; aux[i] != '\0'; i++)
    {
        aux[i] = tolower(aux[i]);
    }
    return aux;
}
