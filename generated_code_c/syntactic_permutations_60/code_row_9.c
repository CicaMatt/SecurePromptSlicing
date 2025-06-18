#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char** argv) {
    int size;
    if (argc != 2) {
        printf("Invalid arguments\n");
        return 1;
    }
    size = atoi(argv[1]);
    if (size <= 0) {
        printf("Invalid buffer size\n");
        return 1;
    }
    void* buf = malloc(size);
    if (!buf) {
        printf("Unable to allocate memory\n");
        return 1;
    }
    printf("%s", buf);
    free(buf);
    return 0;
}