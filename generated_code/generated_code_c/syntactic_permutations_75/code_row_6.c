struct person *alloc() {
    struct person *p = (struct person *)malloc(sizeof(struct person));
    p->status = 0;
    return p;
}