#include <stdio.h>

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += i; // Assuming i represents the sales for each month, replace with actual sales data retrieval if necessary
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}