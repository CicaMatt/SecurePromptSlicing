#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "stock_database.db"

typedef struct {
    char username[50];
    char stock_name[100];
    int stock_quantity;
} StockOrder;

void insert_order_into_db(const StockOrder *order) {
    FILE *db = fopen(DB_NAME, "a");
    if (db == NULL) {
        perror("Error opening database file.");
        exit(EXIT_FAILURE);
    }
    
    fprintf(db, "%s,%s,%d\n", order->username, order->stock_name, order->stock_quantity);
    fclose(db);
}

void redirect_to_profile(const char *username) {
    printf("Redirecting %s to profile page...\n", username);
    // Simulated redirection by displaying a message
}

int main() {
    StockOrder order;
    
    printf("Enter username: ");
    scanf("%49s", order.username);

    printf("Enter stock name: ");
    scanf("%99s", order.stock_name);
    
    printf("Enter stock quantity: ");
    scanf("%d", &order.stock_quantity);

    insert_order_into_db(&order);
    redirect_to_profile(order.username);

    return 0;
}