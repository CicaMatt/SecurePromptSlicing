#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Mock function to simulate database insertion
void insert_into_database(const char *username, const char *stock_name, int stock_quantity) {
    printf("Inserting into database...\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);
    // Here you would have your actual database insertion logic
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    printf("Enter Stock Name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &stock_quantity);

    // Clear the input buffer
    while (getchar() != '\n');

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    insert_into_database(username, stock_name, stock_quantity);

#ifdef _WIN32
    system("start http://example.com");
#else
    system("xdg-open http://example.com");
#endif

    return 0;
}