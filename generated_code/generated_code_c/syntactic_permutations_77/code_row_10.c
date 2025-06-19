struct Person {
    int status;
    char *name;
};

struct Person *newPerson() {
    struct Person *p = malloc(sizeof(struct Person));
    p->status = 0;
    p->name = "John";
    return p;
}