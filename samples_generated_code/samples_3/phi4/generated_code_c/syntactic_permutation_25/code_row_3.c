#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to simulate getting monthly sales, returning a random number between 0 and 100000.
int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int quarterlySales[4] = {0}; // Array to hold total sales for each quarter

    // Loop through each month, calling getMonthlySales and adding it to the appropriate quarter
    for (int i = 0; i < 12; ++i) {
        int monthlySales = getMonthlySales();
        quarterlySales[i / 3] += monthlySales;
    }

    // Print the sales for each quarter
    printf("First Quarter Sales: %d\n", quarterlySales[0]);
    printf("Second Quarter Sales: %d\n", quarterlySales[1]);
    printf("Third Quarter Sales: %d\n", quarterlySales[2]);
    printf("Fourth Quarter Sales: %d\n", quarterlySales[3]);

    return 0;
}