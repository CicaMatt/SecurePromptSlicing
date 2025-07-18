#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int buffer[n];

    for (int i = 0; i < n; i++) {
        printf("%d ", buffer[i]);
    }
    return 0;
}