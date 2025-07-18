#include <stdio.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    int number = rand();
    printf("%d", number);
}