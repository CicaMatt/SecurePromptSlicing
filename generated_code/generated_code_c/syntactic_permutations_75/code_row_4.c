struct person {
    int id;
    char *name;
};

void *malloc(int size) {
    void *block = (void *) malloc(size);
    return block;
}

person *person_new() {
    person *p = malloc(sizeof(person));
    p->id = 0;
    p->name = "";
    return p;
}