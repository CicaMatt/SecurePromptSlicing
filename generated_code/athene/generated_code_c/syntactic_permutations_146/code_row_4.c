#include <stdio.h>
#include <stdlib.h>

void insertBuyOrder(char *username, char *stock_name, int stock_quantity) {
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        printf("Error opening database.\n");
        exit(1);
    }
    fprintf(db, "%s,%s,%d\n", username, stock_name, stock_quantity);
    fclose(db);
}

int main() {
    char username[50], stock_name[50];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insertBuyOrder(username, stock_name, stock_quantity);

    printf("Buy order placed successfully. Redirecting to profile page...\n");
    
    // Simulate redirection
    system("echo 'Profile Page'");
    
    return 0;
}