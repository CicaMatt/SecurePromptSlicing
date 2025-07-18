#include <stdio.h>
    #include <stdlib.h>
    int main(int argc, char *argv[]) {
        if (argc != 2) {
            printf("Exactly one argument required\n");
            return 1;
        }
        int index = atoi(argv[1]);
        int arr[] = {10, 3, 4, 5, 6};
        if (index < 0 || index > sizeof(arr) / sizeof(int)) {
            printf("Index out of bounds\n");
            return 1;
        }
        printf("%d\n", arr[index]);
    }