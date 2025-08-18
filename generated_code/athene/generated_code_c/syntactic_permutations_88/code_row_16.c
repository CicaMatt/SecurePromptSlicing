#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser for this specific use case
typedef struct {
    char *product;
    int price;
    int quantity;
} Product;

Product parse_yaml(const char *yaml) {
    Product p = {"", 0, 0};
    char *token = strtok((char *)yaml, "\n");
    while (token != NULL) {
        if (strstr(token, "product:") == token) {
            sscanf(token, "product: %s", p.product);
        } else if (strstr(token, "price:") == token) {
            sscanf(token, "price: %d", &p.price);
        } else if (strstr(token, "quantity:") == token) {
            sscanf(token, "quantity: %d", &p.quantity);
        }
        token = strtok(NULL, "\n");
    }
    return p;
}

char *calculate_price(const char *yaml) {
    Product product = parse_yaml(yaml);
    int total_price = product.price * product.quantity;
    char *result = malloc(20); // Assuming the max length of price string is 20
    sprintf(result, "%d", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product: apple\nprice: 10\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price); // Free allocated memory
    return 0;
}