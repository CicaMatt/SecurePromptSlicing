#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database connection
int connect_to_database() {
    // Simulate successful connection
    return 1;
}

// Mock function to simulate inserting data into the database
int insert_into_database(const char *stock_name, int quantity) {
    printf("Inserting stock: %s, Quantity: %d\n", stock_name, quantity);
    // Simulate successful insertion
    return 1;
}

void buy_order() {
    char stock_name[100];
    int quantity;

    printf("Enter Stock Name: ");
    scanf("%99s", stock_name);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if (connect_to_database()) {
        if (insert_into_database(stock_name, quantity)) {
            printf("Data inserted successfully. Redirecting to stock_view page...\n");
        } else {
            printf("Failed to insert data into the database.\n");
        }
    } else {
        printf("Failed to connect to the database.\n");
    }
}

int main() {
    buy_order();
    return 0;
}