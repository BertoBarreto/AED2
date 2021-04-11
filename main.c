#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct _parts
{
    char part_num[100];
    char name[500];
    char class[500];
    int stock;
    struct _parts *next;
} PARTS;

typedef struct _sets
{
    char set_num[100];
    char name[500];
    int year;
    char theme[500];
    struct _sets *next;
} SETS;

typedef struct _relations
{
    char set_num[100];
    char part_num[100];
    int quantity;
    struct _relations *next;
} RELATIONS;

PARTS *OpenParts(PARTS *parts);
PARTS *InsertPart(PARTS *lst, char *part_num, char *name, char *class, int stock);
SETS *OpenSets(SETS *sets);
SETS *InsertSet(SETS *lst, char *set_num, char *name, int year, char *theme);
RELATIONS *OpenRelations(RELATIONS *relations);
RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num);
PARTS *SearchPartsByClassAndNum(PARTS *parts, char *part_num, char *class);

PARTS *OpenParts(PARTS *parts)
{
    FILE *fp;
    char part_num[100];
    char name[500];
    char class[500];
    int stock;
    PARTS *new_part = (PARTS *)malloc(sizeof(PARTS));
    assert(new_part);

    if (fp = fopen("LEGO-DataSet/parts.tsv", "r"))
    {
        printf("\nGetting parts list...");
        fseek(fp, 25 * sizeof(char), SEEK_SET);
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
    SETS *new_set = (SETS *)malloc(sizeof(SETS));
    assert(new_set);

    if (fp = fopen("LEGO-DataSet/sets.tsv", "r"))
    {
        printf("\nGetting sets list...");
        fseek(fp, 23 * sizeof(char), SEEK_SET);
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
    RELATIONS *new_relation = (RELATIONS *)malloc(sizeof(RELATIONS));
    assert(new_relation);

    if (fp = fopen("LEGO-DataSet/parts_sets.tsv", "r"))
    {
        printf("\nGetting relations list...");
        fseek(fp, 25 * sizeof(char), SEEK_SET);
        while (!feof(fp))
        {

            fscanf(fp, "%[^\t]\t%d\t%[^\n]\n", set_num, &quantity, part_num);
            new_relation = InsertRelation(new_relation, set_num, quantity, part_num);
        }
    }
    fclose(fp);
    return new_relation;
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

RELATIONS *InsertRelation(RELATIONS *lst, char *set_num, int quantity, char *part_num)
{
    assert(set_num);
    assert(part_num);

    RELATIONS *new_relation = (RELATIONS *)malloc(sizeof(RELATIONS));
    assert(new_relation);

    strcpy(new_relation->set_num, set_num);
    strcpy(new_relation->part_num, part_num);
    new_relation->quantity = quantity;
    new_relation->next = lst;

    return new_relation;
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
        printf("%20s - %s\n", lst->set_num, lst->name);
        ListSets(lst->next);
    }
}

void ListRelations(RELATIONS *lst)
{
    if (lst)
    {
        printf("%20s - %s\n", lst->set_num, lst->part_num);
        ListRelations(lst->next);
    }
}

int StockParts(PARTS *lst, int counter)
{
    if (lst)
    {
        counter += lst->stock;
        StockParts(lst->next, counter);
    }
    else
        return counter;
}

PARTS *PartsSearchByClassAndSet(PARTS *parts, RELATIONS *rel, char *class)
{
    PARTS *search = NULL;
    PARTS *partSearch = NULL;
    for (; rel; rel = rel->next)
    {
        //printf("\n%s | %d | %s", rel->set_num, rel->quantity, rel->part_num);
        partSearch = SearchPartsByClassAndNum(partSearch, rel->part_num, class);
        search = InsertPart(search, partSearch->part_num, partSearch->name, partSearch->class, partSearch->stock);
    }
    return search;
}

PARTS *SearchPartsByClassAndNum(PARTS *parts, char *part_num, char *class)
{
    PARTS *search = NULL;
    for (; parts; parts = parts->next)
    {
        if (strcmp(class, parts->class) == 0 && strcmp(part_num, parts->part_num) == 0)
        {
            strcpy(search->part_num, parts->part_num);
            strcpy(search->name, parts->name);
            strcpy(search->class, parts->class);
            search->stock = parts->stock;

            return search;
        }
    }
}

RELATIONS *SearchRelations(RELATIONS *rel, char *set_num)
{
    RELATIONS *search = NULL;

    for (; rel; rel = rel->next)
    {
        if (strcmp(set_num, rel->set_num) == 0)
        {
            printf("\nSet: %20s-%20s", rel->set_num, rel->part_num);
            search = InsertRelation(search, rel->set_num, rel->quantity, rel->part_num);
        }
    }
    return search;
}

SETS *SetsSearchByNum(SETS *sets, char *set_num)
{
    if (!sets || set_num == sets->set_num)
    {
        return sets;
    }
    else
    {
        return SetsSearchByNum(sets->next, set_num);
    }
}

void Menu(PARTS *parts_list, SETS *sets_list, RELATIONS *relations_list)
{
    int option;
    char part_class[100], set_num[100];
    PARTS *search = NULL;
    bool exit = false;
    while (exit != true)
    {
        printf("\n*************************************");
        printf("\n** 1-Total parts in stock          **");
        printf("\n** 2-Search by part class and set  **");
        printf("\n** 0-Exit                          **");
        printf("\n*************************************");
        printf("\nOption: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nParts in stock: %d parts", StockParts(parts_list, 0));
            break;

        case 2:
            fflush(stdin);
            printf("\nPart Class to search: ");
            scanf("%[^\n]", part_class);
            fflush(stdin);
            printf("\nSet Number to search: ");
            scanf("%[^\n]", set_num);
            fflush(stdin);
            //searchPart(parts_list, part_class);
            //SearchRelations(relations_list, set_num);
            //SearchRelations(relations_list, set_num);
            search = PartsSearchByClassAndSet(parts_list, SearchRelations(relations_list, set_num), part_class);

            ListParts(search);
            break;
        case 0:
            exit = true;
            break;

        default:
            break;
        }
    }
}

void main()
{
    PARTS *parts_list = NULL;
    SETS *sets_list = NULL;
    RELATIONS *relations_list = NULL;

    parts_list = OpenParts(parts_list);
    sets_list = OpenSets(sets_list);
    relations_list = OpenRelations(relations_list);
    printf("\nDone!");
    //ListParts(parts_list);
    Menu(parts_list, sets_list, relations_list);
}