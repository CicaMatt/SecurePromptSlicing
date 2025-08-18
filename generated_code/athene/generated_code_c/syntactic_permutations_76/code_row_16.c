#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char name[50];
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p != NULL) {
        memset(p, 0, sizeof(person));
    }
    free(p);
    return 0;
}