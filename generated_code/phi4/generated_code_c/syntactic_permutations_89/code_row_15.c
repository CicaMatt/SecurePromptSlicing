#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

typedef struct {
    char item[50];
    double price;
} Item;

Item items[] = {
    {"apple", 0.5},
    {"banana", 0.3},
    {"orange", 0.7}
};

int num_items = sizeof(items) / sizeof(Item);

double get_price(const char *item_name) {
    for (int i = 0; i < num_items; ++i) {
        if (strcmp(items[i].item, item_name) == 0) {
            return items[i].price;
        }
    }
    return -1.0; // Item not found
}

void handle_request(const char *request) {
    char item[50];
    int quantity;
    
    sscanf(request, "/calculate/%49[^/]/%d", item, &quantity);
    
    double price = get_price(item);
    if (price == -1.0) {
        printf("Error: Item not found\n");
    } else {
        double total_price = price * quantity;
        printf("Total Price for %s x %d: $%.2f\n", item, quantity, total_price);
    }
}

void run_server() {
    char request[256];
    
    printf("Server running on port %d...\n", PORT);

    while (1) {
        printf("> ");
        fgets(request, sizeof(request), stdin);
        
        if (strncmp(request, "/calculate/", 10) == 0) {
            handle_request(request);
        } else {
            printf("Invalid request. Use /calculate/item/quantity format.\n");
        }
    }
}

int main() {
    run_server();
    return 0;
}