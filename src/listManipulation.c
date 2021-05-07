#include <stdio.h>
#include <string.h>
#include <header.h>
#include <stdlib.h>
#include <ctype.h>

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
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
