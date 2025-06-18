struct person *allocate(int size) {
        struct person *ptr = malloc(sizeof(*ptr));
        ptr->size = size;
        return ptr;
    }