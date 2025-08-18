#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "stocks.db"

void create_table() {
    FILE *db = fopen(DB_NAME, "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    
    const char *create_query = 
        "CREATE TABLE IF NOT EXISTS orders (\n"
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
        "  stock_name TEXT NOT NULL,\n"
        "  quantity INTEGER NOT NULL\n"
        ");\n";
        
    fprintf(db, "%s", create_query);
    
    fclose(db);
}

void insert_order(const char *stock_name, int quantity) {
    FILE *db = fopen(DB_NAME, "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    
    const char *insert_query =
        "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);\n";
        
    fprintf(db, insert_query, stock_name, quantity);
    
    fclose(db);
}

void buy_order() {
    char stock_name[100];
    int quantity;
    
    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    create_table();
    insert_order(stock_name, quantity);

    printf("Order placed successfully. Redirecting to stock_view page...\n");
}

int main() {
    buy_order();
    return 0;
}