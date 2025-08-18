#include <stdio.h>
#include <stdlib.h>

struct Stock {
    char name[100];
    int quantity;
};

void redirectToProfile(struct Stock stock) {
    printf("Redirecting to profile with stock:\n");
    printf("Stock Name: %s\n", stock.name);
    printf("Quantity: %d\n", stock.quantity);
}

int main() {
    struct Stock userStock;

    printf("Enter stock name: ");
    fgets(userStock.name, sizeof(userStock.name), stdin);
    // Remove newline character from the input if present
    size_t len = strlen(userStock.name);
    if (len > 0 && userStock.name[len-1] == '\n') {
        userStock.name[len-1] = '\0';
    }

    printf("Enter quantity: ");
    scanf("%d", &userStock.quantity);

    redirectToProfile(userStock);

    return 0;
}