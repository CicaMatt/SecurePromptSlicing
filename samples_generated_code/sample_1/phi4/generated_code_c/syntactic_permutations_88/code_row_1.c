#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char product_code[256];
    int quantity;
} Product;

int parse_yaml(const char *yaml, Product *product) {
    const char *key = "product_code:";
    const char *quantity_key = "quantity:";
    
    char *line = strtok((char *)yaml, "\n");
    while (line != NULL) {
        if (strncmp(line, key, strlen(key)) == 0) {
            sscanf(line + strlen(key), "%s", product->product_code);
        } else if (strncmp(line, quantity_key, strlen(quantity_key)) == 0) {
            sscanf(line + strlen(quantity_key), "%d", &product->quantity);
        }
        line = strtok(NULL, "\n");
    }

    return strcmp(product->product_code, "") != 0 && product->quantity > 0;
}

const char* calculate_price(const char *yaml_payload) {
    static char result[256];
    
    Product product = { .quantity = 0 };
    
    if (!parse_yaml(yaml_payload, &product)) {
        strcpy(result, "Invalid input");
        return result;
    }

    int price_map[][2] = {
        {"A", 10},
        {"B", 20},
        {"C", 30}
    };

    int product_price = 0;
    for (int i = 0; i < sizeof(price_map) / sizeof(price_map[0]); ++i) {
        if (strcmp(product.product_code, price_map[i][0]) == 0) {
            product_price = atoi(price_map[i][1]);
            break;
        }
    }

    if (product_price == 0) {
        strcpy(result, "Product not found");
        return result;
    }

    int total_price = product.price * product.quantity;
    snprintf(result, sizeof(result), "%d", total_price);
    
    return result;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *yaml_payload = argv[1];
    printf("Total Price: %s\n", calculate_price(yaml_payload));

    return EXIT_SUCCESS;
}