#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include"genetic.h"


void merge(struct tuple *a,int left,int mid,int right){
    int size_left= mid -left+1;
    int size_right=right-mid;

    struct tuple * left_arr = (struct tuple *)malloc(sizeof(struct tuple )*size_left);
    struct tuple * right_arr = (struct tuple *)malloc(sizeof(struct tuple )*size_right);
    for(int i=0;i<size_left;i++) left_arr[i]=a[left+i];
    for(int i=0;i<size_right;i++) right_arr[i]=a[mid+i+1];

    int i=0;
    int j=0;
    int k=left;

    while(i<size_left && j<size_right){
        if(left_arr[i].lvl < right_arr[j].lvl){
        a[k++] = left_arr[i++];
        }
        else{
        a[k++] = right_arr[j++];
        }
    }
    if(i<size_left){
        while(i<size_left){
            a[k++] = left_arr[i++];
        
        }
    }
    else{
        while(j<size_right){    
            a[k++] = right_arr[j++];
        }
    }
}
void merge_sort(struct tuple *a, int left, int right){
    if(left>=right){
        return;
    }
    int mid=(left+right)/2;
    merge_sort(a,left,mid);
    merge_sort(a,mid+1,right);
    merge(a,left,mid,right);
} 


void append_main(struct main* skill,struct skillcont value) {
    if (skill->len >= skill->space) {
        int newSpace = skill->space * 2;
        struct skillcont* newArr = (struct skillcont*)malloc(newSpace * sizeof(struct skillcont));
        for (int i = 0; i < skill->len; i++) {
            newArr[i] = skill->arr[i];
        }
        free(skill->arr);
        skill->arr = newArr;
        skill->space = newSpace;
    }
    skill->arr[skill->len] = value;
    skill->len++;
}
void append_skillcont(struct skillcont* cont,struct tuple value) {
    if (cont->len >= cont->space) {
        int newSpace = cont->space * 2;
        struct tuple* newArr = (struct tuple*)malloc(newSpace * sizeof(struct tuple));
        for (int i = 0; i < cont->len; i++) {
            newArr[i] = cont->arr[i];
        }
        free(cont->arr);
        cont->arr = newArr;
        cont->space = newSpace;
    }
    cont->arr[cont->len] = value;
    cont->len++;
}

 int main(){
    FILE *pF = fopen("text3.txt", "r");
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
                //fl append dir hta main_arr.len++ li houwa skills_len
            }
        }
        arr_contributors[i]=x;
    }
    struct project* arr_projects =(struct project*)malloc(sizeof(struct project)*n_projects);
    for(int i = 0; i<n_projects ;i++){
        struct project a;
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
   /*for(int i=0; i<3;i++){
        printf(" %d %s\n", i, arr_contributors[i].name);
    }*/
    //printf("%d\n",skills_len);
    for(int j=0; j<main_arr.len ;j++){
        printf("%d %s\n",j, skills[j].name);
    }
    for(int i=0; i<skills_len ; i++){
        printf("%d  ",i);
        for(int j=0; j<main_arr.arr[i].len ; j++){
            printf(",(%d,%d)\n",main_arr.arr[i].arr[j].cont,main_arr.arr[i].arr[j].lvl);
        }
    }
    printf("\n");
    /*for (int i = 0; i < n_projects; i++) //n_projects
    {
        printf("%s %d  %d\n ",arr_projects[i].name, i, arr_projects[i].n_skill);
        for (int j = 0; j < arr_projects[i].n_skill; j++) //arr_projects[i].n_skill
        {
            printf("(%d,%d),",arr_projects[i].skills[j].cont,arr_projects[i].skills[j].lvl);
        }
        printf("\n");
    }*/
    

    int* rand_project = rand_int(0,n_projects-1);
    

    
    struct population* population;
    population =  creat_population(&main_arr , arr_projects, arr_contributors,  n_projects, n_contributors);
    /* for (int i = 0; i < n_projects * n_projects; i++)
    {
        for (int j = 0; j < population[i].len; j++)
        {
            printf("project %d\n ",population[i].genome[j].project);
            printf("cont ");
            for (int l = 0; l < arr_projects[population[i].genome[j].project].n_skill; l++)
            {
              printf("%d",population[i].genome[j].cont[l]);
            }
            printf("\n");
        }
        printf("\n");
    } */
    struct tuple* best_two = fitness(population , arr_projects ,n_projects);
/*     for (int i = 0; i < 2; i++)
    {
        int pop = best_two[i].cont;
        printf("population:%d\n",pop);
        for (int j = 0; j <population[pop].len ; j++)
        {   
            printf("project:%d\n",population[pop].genome[j].project);
            for (int l = 0; l < arr_projects[population[pop].genome[j].project].n_skill; l++)
            {
                printf("contributor:%d\n",population[pop].genome[j].cont[l]);
            }
            printf("\n");
        }
        printf("\n");
    }
     */

    
    for (int i = 0; i < main_arr.len; i++)
        {
            free(main_arr.arr[i].arr);   
        }
    free(main_arr.arr);
    free(arr_projects);
    free(arr_contributors);
    free(skills);

    return 0;
 }
