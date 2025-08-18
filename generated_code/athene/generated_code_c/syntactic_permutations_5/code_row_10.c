#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int arr[] = {10, 20, 30, 40, 50};
    if (argc != 2) {
        return 1;
    }
    int index = atoi(argv[1]);
    if (index < 0 || index >= 5) {
        return 1;
    }
    printf("%d\n", arr[index]);
    return 0;
}