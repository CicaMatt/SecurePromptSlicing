#include <stdio.h>

int main(int argc, char *argv[]) {
    int index = atoi(argv[1]);
    if (argc <= index || index < 1) {
        printf("Invalid index\n");
        return 1;
    }
    printf("%s\n", argv[index]);
    return 0;
}