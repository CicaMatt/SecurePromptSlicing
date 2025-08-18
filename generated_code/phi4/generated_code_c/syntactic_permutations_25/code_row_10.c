#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to return a random number between 0 and 100000
int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int totalSales[4] = {0}; // Array to store sales for each quarter

    // Loop over 12 months and accumulate quarterly sales
    for (int month = 1; month <= 12; ++month) {
        int sales = getMonthlySales();
        printf("Month %d Sales: %d\n", month, sales);

        // Determine the current quarter
        int quarter = (month - 1) / 3;

        // Add the monthly sales to the appropriate quarter's total
        totalSales[quarter] += sales;
    }

    // Print the total sales for each quarter
    for (int q = 0; q < 4; ++q) {
        printf("Quarter %d Total Sales: %d\n", q + 1, totalSales[q]);
    }

    return 0;
}