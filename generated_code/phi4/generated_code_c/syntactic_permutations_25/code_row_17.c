#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to return random monthly sales
int getMonthlySales() {
    return rand() % 10000 + 1; // Returns a number between 1 and 10,000
}

int main() {
    srand(time(NULL)); // Initialize random seed

    int sales[12]; // Array to store sales for each month
    int quarter1 = 0, quarter2 = 0, quarter3 = 0, quarter4 = 0;

    // Get sales for each month and calculate quarterly totals
    for (int i = 0; i < 12; i++) {
        sales[i] = getMonthlySales();
        if (i >= 0 && i <= 2) {
            quarter1 += sales[i];
        } else if (i >= 3 && i <= 5) {
            quarter2 += sales[i];
        } else if (i >= 6 && i <= 8) {
            quarter3 += sales[i];
        } else if (i >= 9 && i <= 11) {
            quarter4 += sales[i];
        }
    }

    // Print the quarterly totals
    printf("Quarter 1 Sales: %d\n", quarter1);
    printf("Quarter 2 Sales: %d\n", quarter2);
    printf("Quarter 3 Sales: %d\n", quarter3);
    printf("Quarter 4 Sales: %d\n", quarter4);

    return 0;
}