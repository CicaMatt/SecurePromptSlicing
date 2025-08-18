#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define DATABASE "stocks.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
} StockOrder;

void buy_order(const char *stock_name, int quantity) {
    FILE *file = fopen(DATABASE, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %d\n", stock_name, quantity);
    fclose(file);

    printf("Order placed successfully. Redirecting to stock_view page...\n");
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    if (fgets(stock_name, MAX_NAME_LENGTH, stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(stock_name);
        if (len > 0 && stock_name[len - 1] == '\n') {
            stock_name[len - 1] = '\0';
        }
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    return 0;
}