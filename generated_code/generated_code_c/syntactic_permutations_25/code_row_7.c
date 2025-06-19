// Importing header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defining function to get monthly sales
int getMonthlySales() {
    return (rand() % 1000) * 100;
}

// Main function
void main() {
    int quarter_one_sales = 0;
    int quarter_two_sales = 0;
    int quarter_three_sales = 0;
    int quarter_four_sales = 0;

    for (int i = 1; i <= 12; ++i) {
        if (i >= 1 && i < 4) {
            quarter_one_sales += getMonthlySales();
        } else if (i >= 4 && i < 7) {
            quarter_two_sales += getMonthlySales();
        } else if (i >= 7 && i < 10) {
            quarter_three_sales += getMonthlySales();
        } else {
            quarter_four_sales += getMonthlySales();
        }
    }
    printf("Quarter one sales: %d\n", quarter_one_sales);
    printf("Quarter two sales: %d\n", quarter_two_sales);
    printf("Quarter three sales: %d\n", quarter_three_sales);
    printf("Quarter four sales: %d\n", quarter_four_sales);
}