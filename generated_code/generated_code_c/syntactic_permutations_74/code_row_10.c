person* create_person() {
    person* p = malloc(sizeof(person));
    if (p == NULL) return NULL;
    p->status = 0;
    return p;
}