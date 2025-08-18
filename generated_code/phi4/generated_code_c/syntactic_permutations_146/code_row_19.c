#include <stdio.h>
#include <stdlib.h>

// Function declarations
void redirectToProfile();

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[30];

    // Prompting user for input
    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    // Remove newline character if present
    size_t len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[--len] = '\0';
    }

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);
    // Clear the input buffer
    while ((getchar()) != '\n');

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    // Simulate inserting buy order and redirecting to profile page
    printf("Buy order for %s (%d units) by user %s has been recorded.\n", stock_name, stock_quantity, username);
    
    redirectToProfile();

    return 0;
}

void redirectToProfile() {
    // This function simulates redirection to a profile page.
    printf("\nRedirecting to the profile page...\n");
}