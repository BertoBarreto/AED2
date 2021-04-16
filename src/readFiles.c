#include <header.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

PARTS *OpenParts(PARTS *parts)
{
    FILE *fp;
    char part_num[100];
    char name[500];
    char class[500];
    int stock;
    PARTS *new_part = NULL;

    if (fp = fopen("LEGO-DataSet/parts.tsv", "r"))
    {
        printf("\nGetting parts list...");
        fseek(fp, 26 * sizeof(char), SEEK_SET);
        while (!feof(fp))
        {
            fscanf(fp, "\n%[^\t]\t%[^\t]\t%[^\t]\t%d\n", part_num, name, class, &stock);
            new_part = InsertPart(new_part, part_num, name, class, stock);
        }
    }
    fclose(fp);
    return new_part;
}

SETS *OpenSets(SETS *sets)
{
    FILE *fp;
    char set_num[100];
    char name[500];
    char theme[500];
    int year;
    SETS *new_set = NULL;

    if (fp = fopen("LEGO-DataSet/sets.tsv", "r"))
    {
        printf("\nGetting sets list...");
        fseek(fp, 24 * sizeof(char), SEEK_SET);
        while (!feof(fp))
        {
            fscanf(fp, "%[^\t]\t%[^\t]\t%d\t%[^\n]\n", set_num, name, &year, theme);
            new_set = InsertSet(new_set, set_num, name, year, theme);
        }
    }
    fclose(fp);
    return new_set;
}

RELATIONS *OpenRelations(RELATIONS *relations)
{
    FILE *fp;
    char set_num[100];
    char part_num[100];
    int quantity;
    RELATIONS *new_relation = NULL;

    if (fp = fopen("LEGO-DataSet/parts_sets.tsv", "r"))
    {
        printf("\nGetting relations list...");
        fseek(fp, 26 * sizeof(char), SEEK_SET);
        while (!feof(fp))
        {

            fscanf(fp, "%[^\t]\t%d\t%[^\n]\n", set_num, &quantity, part_num);
            new_relation = InsertRelation(new_relation, set_num, quantity, part_num);
        }
    }
    fclose(fp);
    return new_relation;
}
