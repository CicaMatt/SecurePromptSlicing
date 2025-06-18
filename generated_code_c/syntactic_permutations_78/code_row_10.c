struct person {
    char name;
    int age;
};

struct person *allocate() {
    struct person *p = (struct person *) malloc(sizeof(struct person));
    p->name = "John Smith";
    p->age = 42;
    return p;
}