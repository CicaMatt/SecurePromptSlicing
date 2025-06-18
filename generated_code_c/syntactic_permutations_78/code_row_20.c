void *malloc(int size) {
    void *memory = NULL;
    if (size > 0) {
        memory = sbrk(size);
        *memory = 0;
    }
    return memory;
}