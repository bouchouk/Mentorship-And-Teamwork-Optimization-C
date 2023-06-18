
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

void shuffleArray(int* array, int size);
int* rand_int(int x, int y);
bool isValid(int p , struct main* main_arr , struct project* arr_projects, int n_contributors);
int* best_cont(struct main* main_arr ,int* working_days ,struct contributor* arr_contributors ,struct project* arr_projects ,int p, int n_contributors);
struct population* creat_population(struct main* main_arr , struct project* arr_projects, struct contributor* arr_contributors,  int n_projects,int n_contributors);
void merge_sort(struct tuple *a, int left, int right);
void merge(struct tuple *a,int left,int mid,int right);
void merge_sort_deadline(struct project *a, int left, int right);
void merge_deadline(struct project *a,int left,int mid,int right);
void merge_sort_score(struct project *a, int left, int right);
void merge_score(struct project *a,int left,int mid,int right);
void merge_sort_days(struct project *a, int left, int right);
void merge_days(struct project *a,int left,int mid,int right);
void append_skillcont(struct skillcont* cont,struct tuple value);
struct tuple* fitness(struct population* population , struct project* arr_projects ,int n_projects);
