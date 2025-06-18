struct person {
  int age;
  char *name;
  enum status {SINGLE, MARRIED} status;
};

struct person* init_person() {
    struct person* new_person = malloc(sizeof(struct person));
    if (new_person == NULL) {
        printf("Error: cannot allocate memory");
    } else {
        new_person->status = SINGLE;
    }
    return new_person;
}