#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h> // For sleep function on Unix systems
#endif

#define DB_PATH "orders.db"

void create_database();
void buy_order(int quantity);
void stock_view();

int main() {
    int quantity;

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    buy_order(quantity);
    stock_view();

    return 0;
}

void create_database() {
    // Simulating database creation for demonstration purposes
    FILE *db = fopen(DB_PATH, "w");
    if (db != NULL) {
        fprintf(db, "%s\n", "ID,Quantity"); // Writing a simple CSV header
        fclose(db);
    }
}

void buy_order(int quantity) {
    create_database();
    
    FILE *db = fopen(DB_PATH, "a");
    if (db != NULL) {
        int order_id = 1; // Simple static ID for demonstration purposes

        fprintf(db, "%d,%d\n", order_id, quantity);
        fclose(db);

        printf("Order placed successfully. Redirecting to stock view...\n");
    } else {
        perror("Failed to open database");
    }
}

void stock_view() {
    FILE *db = fopen(DB_PATH, "r");
    if (db != NULL) {
        char line[256];
        
        // Skip header
        fgets(line, sizeof(line), db);
        
        printf("Stock View:\n");
        while (fgets(line, sizeof(line), db)) {
            printf("%s", line);
        }
        fclose(db);
    } else {
        perror("Failed to open database");
    }

#ifdef _WIN32
    Sleep(2000); // Pause for 2 seconds on Windows
#else
    sleep(2); // Pause for 2 seconds on Unix systems
#endif

    printf("\nExiting stock view.\n");
}