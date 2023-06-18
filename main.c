#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include"structs.h"
#include"fonctions.h"
// WE WILL PRINT IN THE ./A.OUT THE REVENUE OF ALL GENOMES AND IN THE FILE(Result.txt) WE WILL PRINT THE REQUIRED OUTPUT
 int main(int argc, char**argv){
    FILE *pF = fopen(argv[1], "r");
    int n_contributors;
    int n_projects;
        
    if(pF==NULL){
        printf("Unable to open file!\n");
    }

    fscanf(pF, "%d %d", &n_contributors, &n_projects);
    
    struct main main_arr;
    main_arr.arr=(struct skillcont*)malloc(sizeof(struct skillcont)*10000);
    main_arr.len=0;
    main_arr.space=10000;
    struct contributor* arr_contributors =(struct contributor*)malloc(sizeof(struct contributor)*n_contributors);
    struct name*skills=(struct name*)malloc(sizeof(struct name)*10000000);
    int skills_len=0; 
    for(int i=0; i<n_contributors ; i++){
        struct contributor x;
        int n_skill;
        fscanf(pF,"%s %d",x.name , &n_skill);
        x.value=n_skill;
        for(int j=0; j<n_skill ; j++){
            struct name y;
            int level;
            fscanf(pF, "%s %d" , y.name , &level);
            int a=0;
            int check=1;
            for(int f=0; f<skills_len; f++){
                a=f+1;
                if ( strcmp(y.name, skills[f].name) == 0)
                {   
                    check=0;
                    struct tuple new_cont;
                    new_cont.cont=i;
                    new_cont.lvl=level;
                    append_skillcont(&main_arr.arr[f], new_cont);
                    break;
                }
            }
            if(a==skills_len && check==1){
                skills[skills_len]=y;
                skills_len++;
                struct skillcont new_skill;
                new_skill.arr=(struct tuple*)malloc(sizeof(struct tuple)*10);
                new_skill.len=1;
                new_skill.space=10;
                new_skill.arr[0].cont=i;
                new_skill.arr[0].lvl=level;
                append_main(&main_arr,new_skill);
            }
        }
        arr_contributors[i]=x;
    }
    struct project* arr_projects =(struct project*)malloc(sizeof(struct project)*n_projects);
    for(int i = 0; i<n_projects ;i++){
        struct project a;
        a.index=i;
        fscanf(pF,"%s %d %d %d %d",a.name , &a.days, &a.score , &a.deadline ,&a.n_skill);
        a.skills=(struct tuple*)malloc(sizeof(struct tuple)*a.n_skill);
        for(int j=0 ; j<a.n_skill ; j++){
            struct name y;
            int level;
            struct tuple skill; 
            fscanf(pF, "%s %d" , y.name , &level);
            for(int f=0 ; f<skills_len ; f++){
                 if (strcmp(y.name, skills[f].name) == 0)
                {   
                    skill.cont=f;
                    skill.lvl=level;
                    break; 
                }
            }
            a.skills[j]=skill;
        }
        arr_projects[i]=a;
    }
    fclose(pF);

    for (int i = 0; i < main_arr.len; i++)
    {
        merge_sort(main_arr.arr[i].arr, 0, main_arr.arr[i].len-1);
    }  
    struct population* population;
    population =  creat_population(&main_arr , arr_projects, arr_contributors,  n_projects, n_contributors);

    struct tuple* best_two = fitness(population , arr_projects ,n_projects);
    //best_two[i].cont: the index of the best genome(order of projects)
    //best_two[i].lvl : the score of that genome

//OUT PUT
    FILE *filePtr;
    filePtr = fopen("Result.txt", "w");
    struct genome* best_order = population[best_two[1].cont].genome;
    int len = population[best_two[1].cont].len;
    fprintf(filePtr, "%d\n", len);
    for (int i = 0; i < len; i++)
    {   
        char project[21] ;
        for (int l = 0; l < 21; l++)
        {
            project[l] = arr_projects[best_order[i].project].name[l];
        }
        fprintf(filePtr, "%s\n", project);
        for (int j = 0; j < arr_projects[best_order[i].project].n_skill; j++)
        {   
            char contributor[21] ; 
            for (int l = 0; l < 21; l++)
            {
                contributor[l] = arr_contributors[best_order[i].cont[j]].name[l];
            }
            
            fprintf(filePtr, "%s ", contributor);
        }
        fprintf(filePtr,"\n");   
    }
    fclose(filePtr);
    for (int i = 0; i < main_arr.len; i++)
        {
            free(main_arr.arr[i].arr);   
        }
    for (int i = 0; i < n_projects; i++)
    {
        free(arr_projects[i].skills);
    }
    free(population);
    free(main_arr.arr);
    free(arr_projects);
    free(arr_contributors);
    free(best_two);
    free(skills);

    return 0;
 }
