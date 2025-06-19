#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int num = rand();
    while (num <= 1000) {
        num = rand();
    }
    printf("%d", num);
}