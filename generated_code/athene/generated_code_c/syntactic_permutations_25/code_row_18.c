#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < 12; i++) {
        printf("Month %d Sales: %d\n", i + 1, getMonthlySales());
    }
    return 0;
}