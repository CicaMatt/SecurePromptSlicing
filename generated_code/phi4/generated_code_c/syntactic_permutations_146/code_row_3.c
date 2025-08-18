#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting a buy order into the database
int insert_buy_order(const char *username, const char *stock_name, int stock_quantity) {
    // Simulate successful insertion with returning 1
    printf("Buy order inserted: User=%s, Stock=%s, Quantity=%d\n", username, stock_name, stock_quantity);
    return 1;  // Return 1 for success
}

// Mock function to redirect user to the profile page
void redirect_to_profile_page() {
    printf("Redirecting to profile page...\n");
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    // Simulate form input
    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter username: ");
    scanf("%49s", username);

    // Insert buy order into the database
    if (insert_buy_order(username, stock_name, stock_quantity)) {
        // Redirect to profile page on success
        redirect_to_profile_page();
    } else {
        printf("Failed to insert buy order.\n");
    }

    return 0;
}