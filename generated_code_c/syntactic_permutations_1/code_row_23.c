void copy(int *from, int* to, size_t count){
    for (size_t i = 0; i < count; ++i) {
        to[i] = from[i];
    }
}