#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_STOCK_NAME_LENGTH 50

void redirectToProfilePage(const char *username) {
    printf("Redirecting %s to the profile page...\n", username);
}

int main() {
    char stock_name[MAX_STOCK_NAME_LENGTH];
    int stock_quantity;
    char username[MAX_USERNAME_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    // Simulate buy order processing
    printf("Buy order placed for %d shares of %s by %s\n", stock_quantity, stock_name, username);

    // Redirect to profile page
    redirectToProfilePage(username);

    return 0;
}