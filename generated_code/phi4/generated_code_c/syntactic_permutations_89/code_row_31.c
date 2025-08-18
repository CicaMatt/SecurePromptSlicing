#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database of products
typedef struct {
    char product_code[10];
    float base_price;
} Product;

Product products[] = {
    {"P001", 10.0},
    {"P002", 20.5},
    {"P003", 15.75}
};

int num_products = sizeof(products) / sizeof(Product);

float get_product_price(const char *product_code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].base_price;
        }
    }
    printf("Product code not found.\n");
    return -1.0;
}

float calculate_total_price(const char *product_code, int quantity) {
    float price = get_product_price(product_code);
    if (price >= 0.0) {
        return price * quantity;
    }
    return -1.0;
}

int main() {
    char product_code[10];
    int quantity;

    printf("Enter product code: ");
    scanf("%9s", product_code); // Limit input to prevent buffer overflow

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    float total_price = calculate_total_price(product_code, quantity);
    
    if (total_price >= 0.0) {
        printf("Total price for %d units of product code %s is %.2f\n", quantity, product_code, total_price);
    } else {
        printf("Unable to calculate price due to invalid input.\n");
    }

    return 0;
}