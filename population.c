//THE FONCTION USED HERE ARE IN GENETIC_FONCTIONS.C

//WE WILL INITIALIZE OUR POPULATION WHISH IS THE ONLY GENERATION CAUSE WE DIDN'T HAVE ENOUGH TIME TO FIXE OTHER GENERATIONS PROBLEMS
//THE FIRST 8 GENOME ARE BASED ON SOTING THE ARR OF PROJECTS, THE OTHERS ARE RANDOM BUT THEY GO THROUGH CREAT_GENOME FONCTION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include"structs.h"
#include"fonctions.h"

struct population* creat_population(struct main* main_arr1 , struct project* arr_projects, struct contributor* arr_contributors,  int n_projects, int n_contributors){
    //initialise the population
    int pop_size = n_projects * n_projects;
    if (pop_size > 100)
    {
        pop_size=100;
    }
    struct population*population = (struct population*)malloc(sizeof(struct population)*pop_size);
    //////////////////////////GENOME OF SORTED ARRAY
    //sorted days
    int* rand_project0 = (int*)malloc(sizeof(int)*n_projects);
    struct project* sorted_project_days = (struct project*)malloc(sizeof(struct project)*n_projects);
    for (int i = 0; i < n_projects; i++)
    {
        sorted_project_days[i]=arr_projects[i];
    }
    merge_sort_days(sorted_project_days,0,n_projects-1);
    for (int i = 0; i < n_projects; i++)
    {
        rand_project0[i] = sorted_project_days[i].index;
    } 
    creat_genome(0 ,rand_project0 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    int* rand_project1 = (int*)malloc(sizeof(int)*n_projects);
    int idx0=n_projects-1;
    //REVESE THE SORTED DAYS
    for (int i = 0; i < n_projects; i++)
    {
        rand_project1[i] = sorted_project_days[idx0].index;
        idx0--;
    }
    creat_genome(1 ,rand_project1 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    free(sorted_project_days);
    //sorted deadline
    int* rand_project2 = (int*)malloc(sizeof(int)*n_projects);
    struct project* sorted_project_deadline= (struct project*)malloc(sizeof(struct project)*n_projects);
    for (int i = 0; i < n_projects; i++)
    {
        sorted_project_deadline[i]=arr_projects[i];
    }
    merge_sort_deadline(sorted_project_deadline,0,n_projects-1);
    for (int i = 0; i < n_projects; i++)
    {
        rand_project2[i] = sorted_project_deadline[i].index;
    }
    creat_genome(2 ,rand_project2 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    //REVERSE THE SORTED DEADLINE
    int* rand_project3 = (int*)malloc(sizeof(int)*n_projects);
    int idx=n_projects-1;
    for (int i = 0; i < n_projects; i++)
    {
        rand_project3[i] = sorted_project_deadline[idx].index;
        idx--;
    }
    creat_genome(3 ,rand_project3 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    free(sorted_project_deadline);

    //sorted_score
    int* rand_project4 = (int*)malloc(sizeof(int)*n_projects);
    struct project* sorted_project_score= (struct project*)malloc(sizeof(struct project)*n_projects);
    for (int i = 0; i < n_projects; i++)
    {
        sorted_project_score[i]=arr_projects[i];
    }
    merge_sort_score(sorted_project_score,0,n_projects-1);
    for (int i = 0; i < n_projects; i++)
    {
        rand_project4[i] = sorted_project_score[i].index;
    }
    creat_genome(4 ,rand_project4 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    //REVERSE THE SORTED SCORE
    int* rand_project5 = (int*)malloc(sizeof(int)*n_projects);
    idx = n_projects-1; 
    for (int i = 0; i < n_projects; i++)
    {
        rand_project5[i] = sorted_project_score[idx].index;
        idx--;
    }
    creat_genome(5 ,rand_project5 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    free(sorted_project_score);
    //sorted_n_skill
    int* rand_project6 = (int*)malloc(sizeof(int)*n_projects);
    struct project* sorted_project_n_skill= (struct project*)malloc(sizeof(struct project)*n_projects);
    for (int i = 0; i < n_projects; i++)
    {
        sorted_project_n_skill[i]=arr_projects[i];
    }
    merge_sort_n_skill(sorted_project_n_skill,0,n_projects-1);
    for (int i = 0; i < n_projects; i++)
    {
        rand_project6[i] = sorted_project_n_skill[i].index;
    }
    creat_genome(6 ,rand_project6 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    //REVERSE THE SORTED N_SKILL
    int* rand_project7 = (int*)malloc(sizeof(int)*n_projects);
    idx = n_projects-1; 
    for (int i = 0; i < n_projects; i++)
    {
        rand_project7[i] = sorted_project_n_skill[idx].index;
        idx--;
    }
    creat_genome(7 ,rand_project7 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    free(sorted_project_score);
    ////////////////////////////GENOME OF RANDOM ARRAY
    for (int i = 8; i < pop_size; i++)
    {   
        int* rand_project = rand_int(0,n_projects-1);
        creat_genome(i ,rand_project , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);

    }
    return population;
}
