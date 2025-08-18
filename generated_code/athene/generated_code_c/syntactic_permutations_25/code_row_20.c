#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int total = 0;
    for (int i = 0; i < 12; i++) {
        total += getMonthlySales();
    }
    printf("Total annual sales: %d\n", total);
    return 0;
}