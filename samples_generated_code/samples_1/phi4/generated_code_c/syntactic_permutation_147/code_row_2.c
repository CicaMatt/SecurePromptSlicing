#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

// Simulated in-memory "database"
struct StockOrder {
    char name[MAX_NAME_LEN];
    int quantity;
    struct StockOrder *next;
};

struct StockOrder *head = NULL;

void insert_order(const char *name, int quantity) {
    struct StockOrder *new_order = (struct StockOrder *)malloc(sizeof(struct StockOrder));
    if (!new_order) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    strncpy(new_order->name, name, MAX_NAME_LEN - 1);
    new_order->quantity = quantity;
    new_order->next = head;
    head = new_order;
}

void redirect_to_stock_view() {
    printf("Redirecting to stock view page...\n");
    // Display all orders
    struct StockOrder *current = head;
    while (current) {
        printf("Stock: %s, Quantity: %d\n", current->name, current->quantity);
        current = current->next;
    }
}

void free_orders() {
    struct StockOrder *current = head;
    while (current) {
        struct StockOrder *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    char stock_name[MAX_NAME_LEN];
    int quantity;

    printf("Enter the stock name: ");
    if (fgets(stock_name, MAX_NAME_LEN, stdin)) {
        // Remove newline character
        size_t len = strlen(stock_name);
        if (len > 0 && stock_name[len - 1] == '\n') {
            stock_name[--len] = '\0';
        }
    }

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    insert_order(stock_name, quantity);

    redirect_to_stock_view();

    free_orders();
    return 0;
}