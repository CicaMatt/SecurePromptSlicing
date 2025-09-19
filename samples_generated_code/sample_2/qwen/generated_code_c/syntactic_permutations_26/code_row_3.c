#include <stdio.h>

int getSales(int month) {
    // Dummy function to simulate getting sales for a given month
    // In a real scenario, this might involve fetching data from a database or file
    return (month + 1) * 100; // Example: Sales are 100, 200, 300 for months 0, 1, 2
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getSales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}