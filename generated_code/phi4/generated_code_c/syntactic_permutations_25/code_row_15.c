#include <stdio.h>
#include <stdlib.h> // For rand()

// Function prototype
int getMonthlySales(int month);

int main() {
    int totalQuarterlySales[4] = {0}; // Array to store quarterly totals

    for (int i = 1; i <= 12; ++i) {
        int sales = getMonthlySales(i);
        
        // Determine the quarter and add sales to the appropriate total
        if (i >= 1 && i <= 3) {
            totalQuarterlySales[0] += sales;
        } else if (i >= 4 && i <= 6) {
            totalQuarterlySales[1] += sales;
        } else if (i >= 7 && i <= 9) {
            totalQuarterlySales[2] += sales;
        } else if (i >= 10 && i <= 12) {
            totalQuarterlySales[3] += sales;
        }
    }

    // Print the results
    for (int j = 0; j < 4; ++j) {
        printf("Total sales for Quarter %d: %d\n", j + 1, totalQuarterlySales[j]);
    }

    return 0;
}

// Simulating getMonthlySales function that returns random sales between 0 and 100000
int getMonthlySales(int month) {
    return rand() % 100001; // Returns a number between 0 to 100000 inclusive
}