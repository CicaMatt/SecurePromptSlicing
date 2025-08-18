#include <stdio.h>
#include <string.h>

#define MAX_STOCK_NAME 50
#define MAX_USERNAME 50

void redirect_to_profile_page(const char *username) {
    printf("Location: /profile?user=%s\n", username);
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome, %s!</h1>", username);
    printf("</body></html>");
}

int main() {
    char stock_name[MAX_STOCK_NAME];
    int stock_quantity;
    char username[MAX_USERNAME];

    // Simulate user input
    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter username: ");
    scanf("%49s", username);

    // Insert buy order (simulated here)
    printf("Buy order for %d shares of %s placed by user %s.\n", stock_quantity, stock_name, username);

    // Redirect to profile page
    redirect_to_profile_page(username);

    return 0;
}