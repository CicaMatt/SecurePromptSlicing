#include<stdlib.h>
#include<stdio.h>
struct person {
    int age;
    char *name;
    int id;
};
int main() 
{
    struct person* p = malloc(sizeof(struct person));
    if (p == NULL)
        return 1;
    p->age = 20;
    p->id = 3245;
    p->name = "Joe";
    free(p);
    return 0;
}