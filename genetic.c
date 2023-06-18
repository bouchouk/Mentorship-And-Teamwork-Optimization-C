#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include"genetic.h"


void shuffleArray(int* array, int size) {
    if (size > 1) {
        int i;
        for (i = 0; i < size - 1; i++) {
            int j = i + rand() / (RAND_MAX / (size - i) + 1);
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}

int* rand_int(int x, int y) {
    int size = y - x + 1;
    int* numbers = (int*)malloc(size * sizeof(int));

    // Initialize array with numbers in the desired range
    for (int i = 0; i < size; i++) {
        numbers[i] = x + i;
    }

    // Shuffle the array
    shuffleArray(numbers, size);

    return numbers;
}


int binary_search(struct skillcont* skill , int target) {
    int size = skill->len;
    int low = 0;
    int high = size - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (skill->arr[mid].lvl >= target) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return result;
}


bool isValid(int p , struct main* main_arr , struct project* arr_projects, int n_contributors) {
    int*free_cont=(int*)calloc(sizeof(int),n_contributors); 
    for (int i = 0; i < arr_projects[p].n_skill ; i++)
    {   
        int skill=arr_projects[p].skills[i].cont;
        //printf("skill %d\n",skill);
        int len=main_arr->arr[skill].len -1;
        int x =main_arr->arr[skill].arr[len].cont;
        //printf("cont first %d\n",x);
        int skilled_cont_len = len; //the index of the one who have the biggest lvl in that skill
        while (free_cont[x]==1 && len > -1)
        { 
            //printf("free cont =1\n");
            len--;
            if (len!=-1)
            {
               x = main_arr->arr[skill].arr[len].cont;
            }  
        }
        //printf("len :%d\n", len);
        if(len == -1 && arr_projects[p].skills[i].lvl > 1 ){ //for mentoring someone with 0 lvl 
            free(free_cont);
           // printf("a\n");
            return false;
        }
        else if(len == -1 ){
            free(free_cont);
            //printf("b\n");
            return true;
        }

        else if(arr_projects[p].skills[i].lvl > main_arr->arr[skill].arr[len].lvl+1  || arr_projects[p].skills[i].lvl > main_arr->arr[skill].arr[skilled_cont_len].lvl) {
            free(free_cont);
            //printf("c\n");
            return false;
        }
        else
        {
            //printf("d\n");
            //printf("cont %d\n",x);
            free_cont[x] = 1;
        }
        
    }
    free(free_cont);
    return true;
}
int* best_cont(struct main* main_arr ,int* working_days ,struct contributor* arr_contributors ,struct project* arr_projects ,int p , int n_contrubors){
    //zid l mentoring hna ou update main_arr(lvl)
    int* cont=(int*)malloc(sizeof(int)*arr_projects[p].n_skill);
    int* free_cont = (int*)calloc(sizeof(int),n_contrubors);
    for (int i = 0; i < arr_projects[p].n_skill ; i++){
        int skill=arr_projects[p].skills[i].cont;
        
        if (main_arr->arr[skill].len!=1 )
        {   
            int index = binary_search(&main_arr->arr[skill] , arr_projects[p].skills[i].lvl);
            int real_index = index;
            int cont1 = main_arr->arr[skill].arr[index].cont;
            while(free_cont[cont1]==1 && index < main_arr->arr[skill].len){
                index ++;
                if(index < main_arr->arr[skill].len)
                {
                    cont1 = main_arr->arr[skill].arr[index].cont;
                }
            }
            if(index < main_arr->arr[skill].len-1){
                int index2 = index;
                index2++;
                int cont2 = main_arr->arr[skill].arr[index2].cont;
                while(free_cont[cont2]==1 && index2 < main_arr->arr[skill].len){
                    index2 ++;
                    if(index2 < main_arr->arr[skill].len)
                    {
                        cont2 = main_arr->arr[skill].arr[index2].cont;
                    }
                }
                if (index2 < main_arr->arr[skill].len)
                {
                    if(abs(working_days[cont1]-working_days[cont2])>=(int)((arr_projects[p].days)/2))
                    {
                        if (working_days[cont1] < working_days[cont2]) 
                        {
                            cont[i] = cont1;
                            free_cont[cont[i]]=1;
                            if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[index].lvl)
                            {
                                main_arr->arr[skill].arr[index].lvl++;
                                merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                            }
                        } 
                        else {
                            cont[i] = cont2;
                            free_cont[cont[i]]=1;
                            if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[index2].lvl)
                            {
                                main_arr->arr[skill].arr[index2].lvl++;
                                merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                            }
                        }
                    }
                    else{
                        if(arr_contributors[cont1].value < arr_contributors[cont2].value){
                            cont[i] = cont1;
                            free_cont[cont[i]]=1;
                            if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[index].lvl)
                            {
                                main_arr->arr[skill].arr[index].lvl++;
                                merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                            }
                        }
                        else{
                            cont[i] = cont2;
                            free_cont[cont[i]]=1;
                            if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[index2].lvl)
                            {
                                main_arr->arr[skill].arr[index2].lvl++;
                                merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                            }
                        }
                    }
                }
                else{
                    cont[i] = cont1;
                    free_cont[cont[i]]=1;
                    if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[index].lvl)
                    {
                        main_arr->arr[skill].arr[index].lvl++;
                        merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                    }
                }
            }
            else if (index == main_arr->arr[skill].len-1)
            {
                cont[i] = cont1;
                free_cont[cont[i]]=1;
                if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[index].lvl)
                {
                    main_arr->arr[skill].arr[index].lvl++;
                    merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                }
            }
            else if (index == main_arr->arr[skill].len)
            {
                //in this case the contributor is mentored
                index=real_index;
                cont1 = main_arr->arr[skill].arr[index].cont;
                while(free_cont[cont1]==1 && index > -1)
                {   
                    index--;
                    if (index > -1)
                    {
                        cont1 = main_arr->arr[skill].arr[index].cont;
                    }  
                }
                cont[i] = cont1;
                free_cont[cont[i]]=1;
                if( arr_projects[p].skills[i].lvl==main_arr->arr[skill].arr[index].lvl -1)
                {
                    main_arr->arr[skill].arr[index].lvl++;
                    merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
                }
            }
            
        }
        else if (free_cont[main_arr->arr[skill].arr[0].cont]==0)
        {
            cont[i] = main_arr->arr[skill].arr[0].cont;
            free_cont[cont[i]]=1;
            if(arr_projects[p].skills[i].lvl == main_arr->arr[skill].arr[0].lvl)
            {
                main_arr->arr[skill].arr[0].lvl++;
                merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);
            }

        }
        else if(free_cont[main_arr->arr[skill].arr[0].cont]==1)
        {
            //mentor y who have 0 experience in that skill
            int y;
            if(main_arr->arr[skill].arr[0].cont < (n_contrubors/2))
            {
                y = main_arr->arr[skill].arr[0].cont + 1;
                while(free_cont[y]==1){
                y++;
                }
            }
            else
            {
                y = main_arr->arr[skill].arr[0].cont -1;
                while(free_cont[y]==1){
                y--;
                }
            }
            cont[i]=y;  
            free_cont[y]=1;
            struct tuple new_cont;
            new_cont.cont=y;
            new_cont.lvl=1;
            append_skillcont(&main_arr->arr[skill], new_cont);
            merge_sort(main_arr->arr[skill].arr, 0, main_arr->arr[skill].len-1);

        }
    }
    //update the working_days and the main
    int max_day = -1; //the day of the last one who will end
    for (int i = 0; i < arr_projects[p].n_skill ; i++)
    {
        if(working_days[cont[i]] > max_day){
            max_day=working_days[cont[i]];
        }
    }
    int end_day = max_day + arr_projects[p].days;
    for (int i = 0; i < arr_projects[p].n_skill ; i++){
        working_days[cont[i]] = end_day;
    }
    free(free_cont);
    return cont ;
    

}

///////////////////////////////////////////////////////////////////////////////
void creat_genome(int i ,int*rand_project,struct population* population,struct main* main_arr1 , struct project* arr_projects, struct contributor* arr_contributors,  int n_projects, int n_contributors)
{        
    struct main main_arr ;
    main_arr.arr=(struct skillcont*)malloc(sizeof(struct skillcont)*main_arr1->space);
    main_arr.len = main_arr1->len;
    for (int m = 0; m < main_arr.len; m++)
    {   
        main_arr.arr[m].len = main_arr1->arr[m].len;
        main_arr.arr[m].arr = (struct tuple*)malloc(sizeof(struct tuple)*main_arr.arr[m].len);
        for (int j = 0; j < main_arr.arr[m].len; j++)
        {
            main_arr.arr[m].arr[j].cont = main_arr1->arr[m].arr[j].cont;
            main_arr.arr[m].arr[j].lvl = main_arr1->arr[m].arr[j].lvl;
        }
            
    }
        
    population[i].genome = (struct genome*)malloc(sizeof(struct genome)*n_projects);
    int*working_days=(int*)calloc(sizeof(int),n_contributors); //time axe
    //initialize an array that contain random distinct from project 0 to n-1 
    int rand_project_len=n_projects;
    int g_len=0;
    int x = -1;
     while (rand_project_len!=0 && x!=rand_project_len)
    {   
        int* rand_nonValid = (int*)malloc(sizeof(int)*rand_project_len);//rand_project_len==count
        x=rand_project_len;
        int count=0;//count for nonValidProject
        for (int j = 0; j < x; j++)
        {   
            bool check=isValid(rand_project[j], &main_arr , arr_projects, n_contributors);
            if(check){
                population[i].genome[g_len].project =  rand_project[j];
                population[i].genome[g_len].cont = best_cont(&main_arr ,working_days , arr_contributors, arr_projects ,rand_project[j], n_contributors);
                population[i].genome[g_len].end_day = working_days[population[i].genome[g_len].cont[0]];
                rand_project_len--; 
                g_len++;
            }
             else{
                rand_nonValid[count] = rand_project[j];
                count++;
            }  
        }
        for (int y = 0; y < count; y++)
        {
            rand_project[y]=rand_nonValid[y];            
        } 
        free(rand_nonValid);
    }
    free(rand_project); 
    population[i].len=g_len;
    free(working_days);
    for (int i = 0; i < main_arr.len; i++)
    {
        free(main_arr.arr[i].arr); 
    }
    free(main_arr.arr);
}
///////////////////////////////////////////////////////////////////////////////

struct population* creat_population(struct main* main_arr1 , struct project* arr_projects, struct contributor* arr_contributors,  int n_projects, int n_contributors){
    //initialise the population
    
    int pop_size = n_projects * n_projects;
    if (pop_size > 100)
    {
        pop_size=100;
    }
    
    struct population*population = (struct population*)malloc(sizeof(struct population)*pop_size);
    //genome of sorted array
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
    for (int i = 0; i < n_projects; i++)
    {
        rand_project1[i] = sorted_project_days[idx0].index;
        idx0--;
    }
    creat_genome(1 ,rand_project1 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    printf("hi%d\n",pop_size);
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
    int* rand_project3 = (int*)malloc(sizeof(int)*n_projects);
    int idx1=n_projects-1;
    for (int i = 0; i < n_projects; i++)
    {
        rand_project3[i] = sorted_project_deadline[idx1].index;
        idx1--;
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
    int* rand_project5 = (int*)malloc(sizeof(int)*n_projects);
    int idx2=n_projects-1; 
    for (int i = 0; i < n_projects; i++)
    {
        rand_project5[i] = sorted_project_score[idx2].index;
        idx2--;
    }
    creat_genome(5 ,rand_project5 , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
    free(sorted_project_score);
    //random genome
    for (int i = 6; i < pop_size; i++)
    {   
        printf("main loop %d\n",i);
        int* rand_project = rand_int(0,n_projects-1);
        creat_genome(i ,rand_project , population, main_arr1 , arr_projects, arr_contributors, n_projects, n_contributors);
        
    }
    return population;
}
struct tuple* fitness(struct population* population , struct project* arr_projects ,int n_projects){
    int pop_size = n_projects * n_projects;
    if (pop_size > 100)
    {
        pop_size=100;
    }
    struct tuple *best_two = (struct tuple*)malloc(sizeof(struct tuple)*2);
    //tuple.lvl=is the score ,tuple.cont=is the index of the genome choosen from the population
    best_two[0].lvl=0;
    best_two[1].lvl=0;
    for (int i = 0; i < pop_size; i++)
    {   
        int count = 0;
        for(int j = 0; j < population[i].len; j++)
        {
            int score = arr_projects[population[i].genome[j].project].score;
            int deadline = arr_projects[population[i].genome[j].project].deadline;
            int end_day = population[i].genome[j].end_day;
            if (end_day < deadline )
            {
                count+=score;
            }
            else
            {
                if (end_day - deadline < score)
                {
                    count+=score-(end_day - deadline);
                }
                
            }
        }
        printf("revenue of population %d: %d\n",i,count);
        if (best_two[1].lvl < count)
        {
            best_two[0].lvl = best_two[1].lvl;
            best_two[0].cont = best_two[1].cont;
            best_two[1].lvl = count;
            best_two[1].cont = i;
        }
        else if (best_two[0].lvl < count)
        {
            best_two[0].lvl = count;
            best_two[0].cont = i;
        }
    }
    
return best_two;
}
