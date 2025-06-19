#include <stdio.h>
#include <stdlib.h>

int main() {
    int first = rand() % 991 + 10;
    int second = rand() % 991 + 10;
    
    printf("%d - %d = %d", first, second, first - second);
}