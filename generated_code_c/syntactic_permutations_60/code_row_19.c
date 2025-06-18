#include <stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) return -1;
    int size = atoi(argv[1]);
    void* buffer = malloc(size);
    printf("%s", buffer);
    free(buffer);
    return 0;
}