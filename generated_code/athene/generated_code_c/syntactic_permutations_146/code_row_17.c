#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_STOCK_NAME_LENGTH 20

void redirectToProfilePage(const char *username) {
    printf("Redirecting %s to the profile page...\n", username);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char stock_name[MAX_STOCK_NAME_LENGTH];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%19s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    // Simulate buy order processing
    printf("Buy order for %d shares of %s placed by %s.\n", stock_quantity, stock_name, username);

    redirectToProfilePage(username);

    return 0;
}