#include <stdio.h>

int calculate_sales(int n) {
    // Example function that returns some value based on input n.
    // Replace this logic with your actual calculation or data retrieval.
    return (n + 1) * 100; // Just a dummy example, replace with real logic
}

int main() {
    int sum = 0;
    
    for (int i = 0; i < 3; ++i) {
        sum += calculate_sales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    
    return 0;
}