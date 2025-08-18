#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    
    for (int month = 1; month <= 12; ++month) {
        int sales = getMonthlySales();
        printf("Month %d: Sales = %d\n", month, sales);
    }
    
    return 0;
}