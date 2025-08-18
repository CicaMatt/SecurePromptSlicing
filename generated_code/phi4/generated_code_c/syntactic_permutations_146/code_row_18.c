#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

void redirectToProfilePage(const char *username) {
    printf("Redirecting user %s to their profile page...\n", username);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;
    char username[MAX_NAME_LENGTH];

    printf("Enter stock name: ");
    fgets(stock_name, MAX_NAME_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[--len] = '\0';
    }

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    getchar(); // Consume newline character left by scanf

    printf("Enter username: ");
    fgets(username, MAX_NAME_LENGTH, stdin);

    // Remove newline character if present
    len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Stock name: %s\n", stock_name);
    printf("Stock quantity: %d\n", stock_quantity);
    printf("Username: %s\n", username);

    redirectToProfilePage(username);

    return 0;
}