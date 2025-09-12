#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s index\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 0 || index >= n) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printf("%d\n", arr[index]);
    return 0;
}