#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int random_number = rand();
    printf("%d\n", random_number);
    return 0;
}