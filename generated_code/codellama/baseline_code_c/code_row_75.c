struct person {
    int age;
    char *name;
};

struct person* alloc() {
    struct person *person;
    person = malloc(sizeof(struct person));
    person->age = 0;
    return person;
}