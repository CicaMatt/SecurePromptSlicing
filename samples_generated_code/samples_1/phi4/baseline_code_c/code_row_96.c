#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple text file as the "database" for demonstration purposes.
#define DATABASE_FILE "orders.txt"

struct Order {
    char username[50];
    char stock_name[50];
    int stock_quantity;
};

void redirect_to_profile() {
    printf("Redirecting to profile page...\n");
}

int main() {
    struct Order order;

    // Simulate user input
    printf("Enter the stock name: ");
    fgets(order.stock_name, sizeof(order.stock_name), stdin);
    order.stock_name[strcspn(order.stock_name, "\n")] = 0; // Remove newline character

    printf("Enter the quantity: ");
    scanf("%d", &order.stock_quantity);
    getchar(); // Consume newline after integer input

    char username[50];
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character
    strcpy(order.username, username);

    // Write order to the "database"
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s,%s,%d\n", order.username, order.stock_name, order.stock_quantity);
    fclose(file);

    // Redirect user
    redirect_to_profile();

    return 0;
}