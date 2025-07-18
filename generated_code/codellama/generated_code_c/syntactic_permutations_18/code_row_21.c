int a[] = {1,2,3,4,5};
void printArray(int *a){
    for (size_t i = 0; i < sizeof(a) / sizeof(*a); ++i){
        printf("%d", a[i]);
    }
}