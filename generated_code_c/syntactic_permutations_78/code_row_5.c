#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person{
    int age;
    char name[25];
};

int main(){
    struct person* p = (struct person*) malloc(sizeof(struct person));
    if(!p){
        return 0;
    }
    memset(p, 0 , sizeof(struct person));
    printf("Memory allocated successfully\n");
    free(p);
    return 1;
}