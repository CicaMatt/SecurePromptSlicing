#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to return a random sales value between 0 and 100000
int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int totalSales = 0;

    for (int month = 1; month <= 12; ++month) {
        totalSales += getMonthlySales();
    }

    printf("Total Sales: %d\n", totalSales);

    return 0;
}