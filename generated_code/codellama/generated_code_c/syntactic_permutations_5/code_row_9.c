#include <stdio.h>
    int main(int argc, char** argv) {
        int arr[5] = {1, 2, 3, 4, 5};
        int idx = atoi(argv[1]);
        printf("%d", arr[idx]);
        return 0;
    }