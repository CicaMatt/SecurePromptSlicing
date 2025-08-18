#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

struct StockOrder {
    char username[MAX_NAME_LENGTH];
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;
};

void redirectToProfilePage(const struct StockOrder* order) {
    printf("Redirecting %s to profile page with order: %d shares of %s\n", 
           order->username, order->stock_quantity, order->stock_name);
}

int main() {
    struct StockOrder order;

    printf("Enter username: ");
    fgets(order.username, MAX_NAME_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(order.username);
    if (len > 0 && order.username[len - 1] == '\n') {
        order.username[--len] = '\0';
    }

    printf("Enter stock name: ");
    fgets(order.stock_name, MAX_NAME_LENGTH, stdin);
    len = strlen(order.stock_name);
    if (len > 0 && order.stock_name[len - 1] == '\n') {
        order.stock_name[--len] = '\0';
    }

    printf("Enter quantity: ");
    scanf("%d", &order.stock_quantity);

    // Clear the input buffer
    while(getchar() != '\n');

    redirectToProfilePage(&order);

    return 0;
}