#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <header.h>
#include <string.h>

void Menu(PARTS *parts_list, SETS *sets_list, RELATIONS *relations_list)
{
    int option;
    char part_class[100], set_num[100], theme[100], class[100], decision;
    PARTS *search_parts = NULL;
    SETS *search_sets = NULL;
    RELATIONS *search_relations = NULL;
    bool exit = false, exists = false;
    while (exit != true)
    {
        printf("\n**************************************************");
        printf("\n** 1-Total parts in stock                       **");
        printf("\n** 2-Search by part class and set               **");
        printf("\n** 3-Search parts by set theme ordering by year **");
        printf("\n** 4-Delete all sets with specific theme        **");
        printf("\n** 5-Total parts in a set                       **");
        printf("\n** 6-See all the parts in a set                 **");
        printf("\n** 7-Delete all parts with specific class       **");
        printf("\n** 8-Wich part is more used in diferent sets    **");
        printf("\n** 0-Exit                                       **");
        printf("\n**************************************************");
        printf("\nOption: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nParts in stock: %d parts", StockParts(parts_list, 0));
            break;

#pragma region Part_Class_To_Search
        case 2:
            fflush(stdin);
            printf("\nPart Class to search: ");
            scanf("%[^\n]", part_class);
            while (ExistsClass(parts_list, LowerString(part_class)) == false)
            {
                fflush(stdin);
                printf("There is no part with that class(maybe you wrote it wrong)");
                printf("\nPart Class to search: ");
                scanf("%[^\n]", part_class);
            }

            fflush(stdin);
            printf("\nSet Number to search: ");
            scanf("%[^\n]", set_num);
            while (ExistsSet(sets_list, set_num) == false)
            {
                fflush(stdin);
                printf("\nThere is no Set with that number(maybe you wrote it wrong)");
                printf("\nSet Number to search: ");
                scanf("%[^\n]", set_num);
            }

            search_parts = PartsSearchByClassAndSet(parts_list, SearchRelations(relations_list, set_num), LowerString(part_class));

            if (search_parts)
            {
                printf("\nPart_num    Name    Stock");
                ListPartsStock(search_parts);
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-The set you are searching for doesnt have any parts with that class");
            }

            break;
#pragma endregion

#pragma region Search_By_Theme_Ordered
        case 3:
            fflush(stdin);
            printf("\n Theme to search: ");
            scanf("%[^\n]", theme);
            while (ExistsTheme(sets_list, LowerString(theme)) == false)
            {
                fflush(stdin);
                printf("\n There is no set with that theme(maybe you wrote it wrong)");
                printf("\n Theme to search: ");
                scanf("%[^\n]", theme);
            }

            search_sets = SearchSetbyTheme(sets_list, LowerString(theme));

            if (search_parts)
            {
                OrderSetbyYear(search_sets);

                printf("Name    Theme    Year");
                ListSetsNTY(search_sets);
            }
            else
            {
                printf("\nNot found");
            }
            break;
#pragma endregion

#pragma region Remove_Set_by_Theme
        case 4:
            fflush(stdin);
            printf("\n Sets Theme to remove: ");
            scanf("%[^\n]", theme);
            while (ExistsTheme(sets_list, LowerString(theme)) == false)
            {
                fflush(stdin);
                printf("\n There is no set with that theme");
                printf("\n Sets Theme to remove: ");
                scanf("%[^\n]", theme);
            }

            sets_list = RemoveSetsbyTheme(sets_list, LowerString(theme));

            do
            {
                fflush(stdin);
                printf("\n Do you wish to see the list?[Y/N]");
                scanf("%c", &decision);
            } while (tolower(decision) != 'y' && tolower(decision) != 'n');

            if (decision == 'y')
                ListSets(sets_list);
            break;
#pragma endregion

#pragma region Total_Parts_Needed_In_Set
        case 5:
            fflush(stdin);
            printf("\n Set number: ");
            scanf("%[^\n]", set_num);
            while (ExistsSet(sets_list, LowerString(set_num)) == false)
            {
                fflush(stdin);
                printf("The Set you are looking for doesnt exist(maybe you wrote it wrong)");
                printf("\n Set number: ");
                scanf("%[^\n]", set_num);
            }

            search_parts = PartsSearchBySet(parts_list, SearchRelations(relations_list, set_num));

            if (search_parts)
            {
                printf("\nTotal parts needed: %d parts", StockParts(search_parts, 0));
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-The set you are searching for doesnt have any parts");
            }

            break;
#pragma endregion

#pragma region Parts_Needed_In_Set
        case 6:
            fflush(stdin);
            printf("\n Set number: ");
            scanf("%[^\n]", set_num);
            while (ExistsSet(sets_list, LowerString(set_num)) == false)
            {
                fflush(stdin);
                printf("The Set you are looking for doesnt exist(maybe you wrote it wrong)");
                printf("\n Set number: ");
                scanf("%[^\n]", set_num);
            }

            search_parts = PartsSearchBySet(parts_list, SearchRelations(relations_list, set_num));

            if (search_parts)
            {
                printf("\nPart_num    Name    Stock");
                ListPartsStock(search_parts);
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-The set you are searching for doesnt have any parts");
            }
            break;
#pragma endregion

#pragma region Remove_Part_by_Class
        case 7:
            fflush(stdin);
            printf("\n Part class to remove: ");
            scanf("%[^\n]", class);
            while (ExistsClass(parts_list, LowerString(class)) == false)
            {
                fflush(stdin);
                printf("\n There is no part with that class");
                printf("\n Part class to remove: ");
                scanf("%[^\n]", class);
            }

            parts_list = RemovePartsbyClass(parts_list, LowerString(class));

            do
            {
                fflush(stdin);
                printf("\n Do you wish to see the list?[Y/N]");
                scanf("%c", &decision);
            } while (tolower(decision) != 'y' && tolower(decision) != 'n');

            if (decision == 'y')
                ListParts(parts_list);
            break;
#pragma endregion

#pragma region Remove_Part_by_Class
        case 8:
            printf("The most used part is:");
            ListParts(HighestOccur(parts_list, relations_list));
            break;
#pragma endregion
        case 0:
            exit = true;
            break;

        default:
            printf("Invalid Option");
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
    Menu(parts_list, sets_list, relations_list);
}