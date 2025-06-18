#include <stdlib.h>
    struct Person *allocate_person(void) {
      struct Person *who = malloc(sizeof(struct Person));
      who->status = 0;
      return who;
    }