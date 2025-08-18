#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define DATABASE_FILE "stock_database.txt"

typedef struct {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;
} StockOrder;

void buy_order(const char *stock_name, int quantity) {
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s %d\n", stock_name, quantity);
    fclose(file);
}

void display_stock_view() {
    printf("Stock view page:\n");
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    fclose(file);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, MAX_NAME_LENGTH, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter quantity: ");
    if (scanf("%d", &quantity) != 1) {
        fprintf(stderr, "Invalid input for quantity\n");
        return EXIT_FAILURE;
    }
    
    buy_order(stock_name, quantity);
    display_stock_view();

    return 0;
}