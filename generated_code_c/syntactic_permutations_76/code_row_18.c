struct person * allocate() {
    struct person * p = (struct person *) malloc(sizeof(struct person));
    if(p == NULL) {
        printf("Error: memory allocation failed.");
        exit(1);
    }
    return p;
}