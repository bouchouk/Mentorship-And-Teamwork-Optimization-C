#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include"structs.h"
#include"fonctions.h"


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

void merge_deadline(struct project *a,int left,int mid,int right){
    int size_left= mid -left+1;
    int size_right=right-mid;

    struct project * left_arr = (struct project *)malloc(sizeof(struct project )*size_left);
    struct project * right_arr = (struct project *)malloc(sizeof(struct project )*size_right);
    for(int i=0;i<size_left;i++) left_arr[i]=a[left+i];
    for(int i=0;i<size_right;i++) right_arr[i]=a[mid+i+1];

    int i=0;
    int j=0;
    int k=left;

    while(i<size_left && j<size_right){
        if(left_arr[i].deadline < right_arr[j].deadline){
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
void merge_sort_deadline(struct project *a, int left, int right){
    if(left>=right){
        return;
    }
    int mid=(left+right)/2;
    merge_sort_deadline(a,left,mid);
    merge_sort_deadline(a,mid+1,right);
    merge_deadline(a,left,mid,right);
} 
void merge_days(struct project *a,int left,int mid,int right){
    int size_left= mid -left+1;
    int size_right=right-mid;

    struct project * left_arr = (struct project *)malloc(sizeof(struct project )*size_left);
    struct project * right_arr = (struct project *)malloc(sizeof(struct project )*size_right);
    for(int i=0;i<size_left;i++) left_arr[i]=a[left+i];
    for(int i=0;i<size_right;i++) right_arr[i]=a[mid+i+1];

    int i=0;
    int j=0;
    int k=left;

    while(i<size_left && j<size_right){
        if(left_arr[i].days < right_arr[j].days){
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
void merge_sort_days(struct project *a, int left, int right){
    if(left>=right){
        return;
    }
    int mid=(left+right)/2;
    merge_sort_days(a,left,mid);
    merge_sort_days(a,mid+1,right);
    merge_days(a,left,mid,right);
} 
void merge_score(struct project *a,int left,int mid,int right){
    int size_left= mid -left+1;
    int size_right=right-mid;

    struct project * left_arr = (struct project *)malloc(sizeof(struct project )*size_left);
    struct project * right_arr = (struct project *)malloc(sizeof(struct project )*size_right);
    for(int i=0;i<size_left;i++) left_arr[i]=a[left+i];
    for(int i=0;i<size_right;i++) right_arr[i]=a[mid+i+1];

    int i=0;
    int j=0;
    int k=left;

    while(i<size_left && j<size_right){
        if(left_arr[i].score < right_arr[j].score){
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
void merge_sort_score(struct project *a, int left, int right){
    if(left>=right){
        return;
    }
    int mid=(left+right)/2;
    merge_sort_score(a,left,mid);
    merge_sort_score(a,mid+1,right);
    merge_score(a,left,mid,right);
} 

void merge_n_skill(struct project *a,int left,int mid,int right){
    int size_left= mid -left+1;
    int size_right=right-mid;

    struct project * left_arr = (struct project *)malloc(sizeof(struct project )*size_left);
    struct project * right_arr = (struct project *)malloc(sizeof(struct project )*size_right);
    for(int i=0;i<size_left;i++) left_arr[i]=a[left+i];
    for(int i=0;i<size_right;i++) right_arr[i]=a[mid+i+1];

    int i=0;
    int j=0;
    int k=left;

    while(i<size_left && j<size_right){
        if(left_arr[i].n_skill < right_arr[j].n_skill){
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
void merge_sort_n_skill(struct project *a, int left, int right){
    if(left>=right){
        return;
    }
    int mid=(left+right)/2;
    merge_sort_n_skill(a,left,mid);
    merge_sort_n_skill(a,mid+1,right);
    merge_n_skill(a,left,mid,right);
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
