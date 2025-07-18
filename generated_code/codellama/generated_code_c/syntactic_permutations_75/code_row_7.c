#include <stdlib.h>
struct person
{
    int age;
    char* name;
};
int main(void)
{
    struct person *p;
    p = malloc(sizeof(person));
    if (p == NULL)
    {
        return -1;
    }
    else
    {
        printf("Memory allocated successfully");
        p->age = 0;
        p->name = NULL;
    }
}