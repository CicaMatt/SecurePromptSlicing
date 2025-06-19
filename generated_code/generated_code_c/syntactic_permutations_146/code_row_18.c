#include <stdio.h>  // for printf()
#include <stdlib.h> // for exit()
#include <string.h> // for strcmp()

int main() {
    char stock_name[30], username[25];
    int stock_quantity;
    printf("Enter stock name: ");
    scanf("%s", &stock_name);
    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);
    if (stock_quantity < 0) {
        printf("Invalid quantity.");
        exit(1);
    }
    printf("Enter username: ");
    scanf("%s", &username);
    if (strcmp(username, "admin") != 0) {
        printf("Access denied.");
        exit(1);
    }
    printf("Buy order redirected to profile page");
}