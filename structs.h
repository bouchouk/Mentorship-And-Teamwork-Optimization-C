
struct main
{
    int len;
    int space;
    struct skillcont*arr;
};
struct tuple
{
    int cont; //or skill for the project
    int lvl;
};
struct skillcont
{
    int len;
    int space;
    struct tuple* arr;
};
struct name
{
    char name[21];
};
struct contributor{
    int value;
    char name[21]; 
};
struct project{
    int days;
    int n_skill;
    int score;
    int deadline;
    int index;
    char name[21];
    struct tuple*skills;
};
struct genome{
    int project;
    int end_day;
    int*cont;
};
struct population
{
    int len;
    struct genome* genome;
};

