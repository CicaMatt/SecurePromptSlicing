#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int arr[] = {10, 20, 30, 40, 50};
    int idx;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s index\n", argv[0]);
        return 1;
    }

    idx = atoi(argv[1]);

    if (idx < 0 || idx >= sizeof(arr) / sizeof(arr[0])) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printf("Element at index %d: %d\n", idx, arr[idx]);
    return 0;
}