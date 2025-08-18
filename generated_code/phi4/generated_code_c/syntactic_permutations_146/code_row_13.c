#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
int insertBuyOrder(const char *stockName, int quantity) {
    // In a real scenario, this would involve database operations.
    printf("Inserting buy order into the database:\n");
    printf("Stock Name: %s\n", stockName);
    printf("Quantity: %d\n", quantity);
    
    // Simulate successful insertion
    return 1; 
}

// Mock function to simulate redirect to profile page
void redirectToProfilePage() {
    printf("\nRedirecting to the profile page...\n");
    system("start https://example.com/profile"); // Example URL, replace with actual profile page URL
}

int main() {
    char stockName[100];
    int quantity;
    
    printf("Enter stock name: ");
    scanf("%99s", stockName); // Read up to 99 characters to prevent overflow

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (insertBuyOrder(stockName, quantity)) {
        redirectToProfilePage();
    } else {
        printf("\nFailed to insert buy order. Please try again.\n");
    }

    return 0;
}