#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include"structs.h"
#include"fonctions.h"

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
