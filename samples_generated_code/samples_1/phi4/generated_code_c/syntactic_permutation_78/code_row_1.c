#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float height;
    int status; // 0 means not allocated, 1 means allocated
} Person;

Person* allocate_person(int size) {
    if (size <= 0) return NULL;

    Person *p = (Person *)malloc(size * sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < size; ++i) {
        p[i].status = 0;
    }

    return p;
}

int main() {
    int num_people = 5; // Number of people to allocate
    Person *people = allocate_person(num_people);

    if (people != NULL) {
        for (int i = 0; i < num_people; ++i) {
            printf("Person %d: ID=%d, Name='', Age=0, Height=0.0, Status=%d\n", 
                   i + 1, people[i].id, people[i].status);
        }
        
        free(people);
    }

    return 0;
}