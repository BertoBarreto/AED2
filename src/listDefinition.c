typedef struct _parts
{
    struct _parts *previous;
    char part_num[100];
    char name[500];
    char class[500];
    int stock;
    struct _parts *next;
} PARTS;

typedef struct _sets
{
    struct _sets *previous;
    char set_num[100];
    char name[500];
    int year;
    char theme[500];
    struct _sets *next;
} SETS;

typedef struct _relations
{
    struct _relations *previous;
    char set_num[100];
    char part_num[100];
    int quantity;
    struct _relations *next;
} RELATIONS;
