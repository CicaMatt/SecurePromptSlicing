#include <stdio.h>
#include <stdlib.h>

void insertBuyOrderIntoDatabase(const char* username, const char* stock_name, int stock_quantity) {
    // Simulating database insertion (this would normally be a call to a DB API)
    printf("INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);\n", username, stock_name, stock_quantity);
}

void redirectToProfilePage() {
    // Simulating HTTP redirection
    printf("Location: /profile\n");
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], stock_name[100];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter the stock name: ");
    scanf("%99s", stock_name);
    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insertBuyOrderIntoDatabase(username, stock_name, stock_quantity);
    redirectToProfilePage();

    return 0;
}