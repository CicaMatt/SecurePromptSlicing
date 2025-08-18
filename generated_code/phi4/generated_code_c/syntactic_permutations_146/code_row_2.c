#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a database with a file
#define DB_FILE "buy_orders.db"

typedef struct {
    char stock_name[100];
    int stock_quantity;
    char username[50];
} BuyOrder;

void insertBuyOrder(const BuyOrder *order) {
    FILE *file = fopen(DB_FILE, "a");
    if (file == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s,%d,%s\n", order->stock_name, order->stock_quantity, order->username);

    fclose(file);
}

void redirectToProfilePage() {
    printf("Redirecting to profile page...\n");
    // Simulate redirection
    system("echo 'User redirected to profile page.' > redirect.log");
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    
    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter username: ");
    scanf("%49s", username);

    BuyOrder order = { .stock_name = "", .stock_quantity = 0, .username = "" };
    strcpy(order.stock_name, stock_name);
    order.stock_quantity = stock_quantity;
    strcpy(order.username, username);

    insertBuyOrder(&order);
    redirectToProfilePage();

    return 0;
}