#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct _parts
{
    char part_num[50];
    char name[500];
    char class[500];
    int stock;
    struct _parts *next;
} PARTS;

typedef struct _sets
{
    char set_num[50];
    char name[500];
    int year;
    char theme[500];
    struct _sets *next;
} SETS;

PARTS *OpenParts(PARTS *parts);
PARTS *InsertPart(PARTS *lst, char *part_num, char *name, char *class, int stock);
SETS *OpenSets(SETS *sets);
SETS *InsertSet(SETS *lst, char *set_num, char *name, int year, char *theme);

PARTS *OpenParts(PARTS *parts)
{
    FILE *fp;
    int i = 0;
    char trash[1000];
    char part_num[100];
    char name[500];
    char class[500];
    int stock;
    PARTS *new_part = (PARTS *)malloc(sizeof(PARTS));
    assert(new_part);

    if (fp = fopen("LEGO-DataSet/parts.tsv", "r"))
    {
        while (!feof(fp))
        {

            if (i == 0)
            {
                printf("\nEntrou");
                fscanf(fp, "%[^\n]\n", trash);
                printf("Trash:%s", trash);
            }
            else if (i > 0)
            {
                fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%d\n", part_num, name, class, &stock);
                parts = InsertPart(parts, part_num, name, class, stock);
                strcpy(new_part->part_num, part_num);
                strcpy(new_part->name, name);
                strcpy(new_part->class, class);
                new_part->stock = stock;
                new_part->next = parts;
            }
            i++;
        }
    }
    return new_part;
}

SETS *OpenSets(SETS *sets)
{
    FILE *fp;
    int i = 0;
    char trash[1000];
    char set_num[100];
    char name[500];
    char theme[500];
    int year;
    SETS *new_set = (SETS *)malloc(sizeof(SETS));
    assert(new_set);

    if (fp = fopen("LEGO-DataSet/sets.tsv", "r"))
    {
        while (!feof(fp))
        {

            if (i == 0)
            {
                printf("\nEntrou");
                fscanf(fp, "%[^\n]\n", trash);
                printf("Trash:%s", trash);
            }
            else if (i > 0)
            {
                fscanf(fp, "%[^\t]\t%[^\t]\t%d\t%[^\n]\n", set_num, name, &year, theme);
                sets = InsertSet(sets, set_num, name, year, theme);
                strcpy(new_set->set_num, set_num);
                strcpy(new_set->name, name);
                strcpy(new_set->theme, theme);
                new_set->year = year;
                new_set->next = sets;
            }
            i++;
        }
    }
    return new_set;
}

PARTS *InsertPart(PARTS *lst, char *part_num, char *name, char *class, int stock)
{
    assert(part_num);
    assert(name);
    assert(class);

    PARTS *new_part = (PARTS *)malloc(sizeof(PARTS));
    assert(new_part);

    strcpy(new_part->part_num, part_num);
    strcpy(new_part->name, name);
    strcpy(new_part->class, class);
    new_part->stock = stock;
    new_part->next = lst;

    return new_part;
}

SETS *InsertSet(SETS *lst, char *set_num, char *name, int year, char *theme)
{
    assert(set_num);
    assert(name);
    assert(theme);

    SETS *new_set = (SETS *)malloc(sizeof(SETS));
    assert(new_set);

    strcpy(new_set->set_num, set_num);
    strcpy(new_set->name, name);
    strcpy(new_set->theme, theme);
    new_set->year = year;
    new_set->next = lst;

    return new_set;
}

void ListParts(PARTS *lst)
{
    if (lst)
    {
        printf("%20s - %s\n", lst->part_num, lst->name);
        ListParts(lst->next);
    }
}

void ListSets(SETS *lst)
{
    if (lst)
    {
        printf("%s - %s\n", lst->set_num, lst->name);
        ListSets(lst->next);
    }
}
int StockParts(PARTS *lst, int contador)

{
    if (lst)
    {
        contador += lst->stock;
        StockParts(lst->next, contador);
    }
    else
        return contador;
}

void main()
{
    PARTS *parts_list = NULL;
    SETS *sets_list = NULL;

    parts_list = OpenParts(parts_list);
    sets_list = OpenSets(sets_list);
    //ListParts(parts_list);

    printf("\n%d", StockParts(parts_list, 0));
    //ListSets(sets_list);
}