#include <stdio.h>
#include <stdlib.h>
 
struct person {
    char *name;
    int age;
};
 
int main() {
  struct person *p = malloc(sizeof(person));
  p->status = "active";
}