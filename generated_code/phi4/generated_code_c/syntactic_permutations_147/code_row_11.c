#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for demonstration purposes
void redirectToStockViewPage() {
    printf("Redirecting to stock_view page...\n");
}

int insertIntoDatabase(const char *stockName, int quantity) {
    // In a real application, you would use database-specific libraries like MySQL or SQLite.
    // Here we simulate the insertion with a simple print statement.
    
    printf("Inserting into database: Stock Name = %s, Quantity = %d\n", stockName, quantity);
    return 1; // Return 1 to indicate success
}

int main() {
    char stockName[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stockName);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (insertIntoDatabase(stockName, quantity)) {
        redirectToStockViewPage();
    }

    return 0;
}