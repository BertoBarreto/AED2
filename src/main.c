#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <header.h>
#include <parts.h>
#include <relations.h>
#include <sets.h>

void Menu(PARTS *parts_list, SETS *sets_list, RELATIONS *relations_list)
{
    int option, quantity, year;
    SETS *newSet = NULL;
    PARTS *part_Set = NULL;
    RELATIONS *newRel = NULL;
    char part_num[100], part_class[100], part_name[100],
        set_name[100], set_num[100], theme[100], decision;

    PARTS *search_parts = NULL;
    SETS *search_sets = NULL;
    RELATIONS *search_relations = NULL;
    bool exit = false, exists = false;

    clock_t t;
    double time_taken;

    while (exit != true)
    {
        fflush(stdin);
        printf("\n**************************************************");
        printf("\n** 1-Search set by theme ordered by year        **");
        printf("\n** 2-Search by part class and set               **");
        printf("\n** 3-See all the parts in a set                 **");
        printf("\n** 4-Total parts in stock                       **");
        printf("\n** 5-Total parts in a set                       **");
        printf("\n** 6-Wich part is more used in diferent sets    **");
        printf("\n** 7-Sets that can be built with the stock      **");
        printf("\n** 8-Edit parts number in stock (TODO)          **");
        printf("\n** 9-Add set and set parts to stock             **");
        printf("\n** 10-Delete all parts with specific class      **");
        printf("\n** 11-Delete all sets with specific theme       **");
        printf("\n** 0-Exit                                       **");
        printf("\n**************************************************");
        printf("\nOption: ");
        scanf("%d", &option);
        switch (option)
        {
#pragma region Search_By_Theme_Ordered
        case 1:
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

            if (search_sets)
            {
                OrderSetbyYear(search_sets);

                printf("\nName    Theme    Year");
                ListSetsNTY(search_sets);
            }
            else
            {
                printf("\nNot found");
            }
            break;
#pragma endregion

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

#pragma region Parts_Needed_In_Set
        case 3:
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
            search_relations = SearchRelations(relations_list, set_num);
            search_parts = PartsSearchBySet(parts_list, search_relations);

            if (search_parts)
            {
                printf("\nPart_num    Name  Class   Stock   Quantity");
                ListPartsAndRelations(search_parts, search_relations);
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-The set you are searching for doesnt have any parts");
            }
            break;
#pragma endregion

        case 4:
            printf("\nParts in stock: %d parts", StockParts(parts_list));
            break;

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

            search_relations = SearchRelations(relations_list, set_num);

            if (search_relations)
            {
                printf("\nTotal parts needed: %d parts", SetPartsQuantity(search_relations));
            }
            else
            {
                printf("\nNot found, reasons:");
                printf("\n-The set you are searching for doesnt have any parts");
            }

            break;
#pragma endregion

#pragma region Most_Used_Part
        case 6:
            t = clock();
            printf("The most used part is: ");
            printf("\n%s", MoreUsedPart(relations_list));
            t = clock() - t;
            time_taken = ((double)t) / CLOCKS_PER_SEC;
            printf("\n Took: %f seconds", time_taken);

            break;
#pragma endregion

#pragma region Sets_Can_Be_Built
        case 7:
            t = clock();
            search_sets = SearchSetCanBuild(sets_list, relations_list, parts_list);
            ListSets(search_sets);
            t = clock() - t;
            time_taken = (((double)t) / CLOCKS_PER_SEC) / 60;
            printf("\n Took: %f minutes", time_taken);

            break;
#pragma endregion

#pragma region Sets_Can_Be_Built
        case 8:

            break;
#pragma endregion

#pragma region Add_Set_Parts
        case 9:

            fflush(stdin);
            printf("\nSet num: ");
            scanf("%[^\n]", set_num);
            fflush(stdin);
            printf("\nSet name: ");
            scanf("%[^\n]", set_name);
            fflush(stdin);
            printf("\nSet theme: ");
            scanf("%[^\n]", theme);
            fflush(stdin);
            printf("\nSet year: ");
            scanf("%d", &year);
            sets_list = InsertSets(sets_list, set_num, set_name,
                                   year, theme);
            do
            {
                fflush(stdin);
                printf("Do you wish to add a new part?[Y/N]");
                scanf("%c", &decision);
                if (tolower(decision) == 'y')
                {
                    fflush(stdin);
                    printf("\nPart num: ");
                    scanf("%[^\n]", part_num);
                    fflush(stdin);
                    printf("\nPart name: ");
                    scanf("%[^\n]", part_name);
                    fflush(stdin);
                    printf("\nPart class: ");
                    scanf("%[^\n]", part_class);
                    fflush(stdin);
                    printf("\nPart quantity: ");
                    scanf("%d", &quantity);

                    parts_list = InsertPart(parts_list, part_num,
                                            part_name, part_class, quantity);
                    relations_list = InsertRelation(relations_list, set_num,
                                                    quantity, part_num);
                }
                else
                {

                    fflush(stdin);
                    printf("\nPart num: ");
                    scanf("%[^\n]", part_num);
                    while (ExistsPart(parts_list, part_num) == false)
                    {
                        fflush(stdin);
                        printf("There is no part with that part_num (maybe you wrote it wrong)");
                        printf("\nPart num: ");
                        scanf("%[^\n]", part_num);
                    }
                    fflush(stdin);
                    printf("\nPart quantity: ");
                    scanf("%d", &quantity);

                    search_parts = SearchPartsByNum(parts_list, part_num);

                    search_parts->stock += quantity;

                    relations_list = InsertRelation(relations_list, set_num, quantity, part_num);
                }
                fflush(stdin);
                printf("\nDo u wish to add more parts?[Y/N]");
                scanf("%c", &decision);
            } while (tolower(decision) == 'y');

            search_relations = SearchRelations(relations_list, newSet->set_num);

            ListRelations(search_relations);

            break;
#pragma endregion

#pragma region Remove_Part_by_Class
        case 10:
            fflush(stdin);
            printf("\n Part class to remove: ");
            scanf("%[^\n]", part_class);
            while (ExistsClass(parts_list, LowerString(part_class)) == false)
            {
                fflush(stdin);
                printf("\n There is no part with that class");
                printf("\n Part class to remove: ");
                scanf("%[^\n]", part_class);
            }

            parts_list = RemovePartsbyClass(parts_list, LowerString(part_class));

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

#pragma region Remove_Set_by_Theme
        case 11:
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

    //experimentar o valgrind;
    Menu(parts_list, sets_list, relations_list);
}