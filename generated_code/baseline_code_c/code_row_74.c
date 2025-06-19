#include <stdlib.h>

struct Person {
    int status;
};

Person* allocate() {
    return (Person*)malloc(sizeof(Person));
}

int main() {
    Person* p = allocate();
    p->status = 0;
    return 0;
}