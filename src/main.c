#include <stdio.h>
#include <stdbool.h>
#include <header.h>

void Menu(PARTS *parts_list, SETS *sets_list, RELATIONS *relations_list)
{
    int option;
    char part_class[100], set_num[100], theme[100];
    PARTS *search_parts = NULL;
    SETS *search_sets = NULL;
    RELATIONS *search_relations = NULL;
    bool exit = false;
    while (exit != true)
    {
        printf("\n*************************************");
        printf("\n** 1-Total parts in stock          **");
        printf("\n** 2-Search by part class and set  **");
        printf("\n** 3-Search by theme               **");
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
            search_parts = PartsSearchByClassAndSet(parts_list, SearchRelations(relations_list, set_num), part_class);
            if (search_parts)
            {
                printf("\nPart_num    Name    Stock");
                ListPartsStock(search_parts);
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-The set you are searching for doesnt have any parts with that class");
                printf("\n-The set that you are looking for doesnt exist(maybe you wrote it wrong)");
                printf("\n-The class of parts that you are looking for doesnt exist(maybe you wrote it wrong)");
            }
            break;
        case 3:
            fflush(stdin);
            printf("\n Theme to search: ");
            scanf("%[^\n]", theme);

            LowerString(theme);

            search_sets = SearchSetbyTheme(sets_list, theme);
            if (search_parts)
            {
                OrderSetbyYear(search_sets);

                printf("Name    Theme    Year");
                ListSetsNTY(search_sets);
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-There is no set with that theme");
                printf("\n-The theme that you are looking for doesnt exist(maybe you wrote it wrong)");
            }
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
    RemoveSetsbyTheme(sets_list, "Castle");
    ListSets(sets_list);

    Menu(parts_list, sets_list, relations_list);
}