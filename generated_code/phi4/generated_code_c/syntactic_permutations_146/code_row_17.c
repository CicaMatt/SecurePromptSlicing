#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_QUANTITY_LENGTH 10

void redirectToProfilePage(const char *username) {
    printf("Redirecting %s to their profile page...\n", username);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    char stock_quantity[MAX_QUANTITY_LENGTH];
    char username[50];

    printf("Enter stock name: ");
    fgets(stock_name, MAX_NAME_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[--len] = '\0';
    }

    printf("Enter quantity: ");
    fgets(stock_quantity, MAX_QUANTITY_LENGTH, stdin);
    // Remove newline character if present
    len = strlen(stock_quantity);
    if (len > 0 && stock_quantity[len - 1] == '\n') {
        stock_quantity[--len] = '\0';
    }

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %s\n", stock_quantity);
    printf("Username: %s\n", username);

    redirectToProfilePage(username);

    return 0;
}