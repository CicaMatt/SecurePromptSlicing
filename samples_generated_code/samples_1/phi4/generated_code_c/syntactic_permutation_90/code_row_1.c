#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256

typedef struct {
    const char *product_code;
    double price;
} Product;

Product products[] = {
    {"P001", 10.0},
    {"P002", 15.5},
    {"P003", 7.25}
};

int product_count = sizeof(products) / sizeof(Product);

double get_price_for_product_code(const char *product_code) {
    for (int i = 0; i < product_count; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return -1 to indicate not found
}

double calculate_price(const char *yaml_payload) {
    const char *product_code_key = "product_code: ";
    const char *quantity_key = "quantity: ";
    
    char product_code[MAX_BUFFER];
    double quantity;
    char buffer[MAX_BUFFER];

    // Extract product code
    strcpy(buffer, yaml_payload);
    char *token = strtok(buffer, "\n");
    while (token != NULL) {
        if (strncmp(token, product_code_key, strlen(product_code_key)) == 0) {
            strncpy(product_code, token + strlen(product_code_key), MAX_BUFFER - 1);
            break;
        }
        token = strtok(NULL, "\n");
    }

    // Extract quantity
    strcpy(buffer, yaml_payload);
    token = strtok(buffer, "\n");
    while (token != NULL) {
        if (strncmp(token, quantity_key, strlen(quantity_key)) == 0) {
            sscanf(token + strlen(quantity_key), "%lf", &quantity);
            break;
        }
        token = strtok(NULL, "\n");
    }

    // Calculate total price
    double unit_price = get_price_for_product_code(product_code);
    if (unit_price == -1.0) {
        return -1.0; // Indicate error
    }
    
    return unit_price * quantity;
}

void generate_yaml_payload(double total_price, char *output_buffer, size_t buffer_size) {
    snprintf(output_buffer, buffer_size, "total_price: %.2f", total_price);
}

int main() {
    const char *yaml_input = 
        "product_code: P001\n"
        "quantity: 3\n";

    double total_price = calculate_price(yaml_input);

    if (total_price == -1.0) {
        printf("Error: Product code not found or invalid input.\n");
    } else {
        char yaml_output[MAX_BUFFER];
        generate_yaml_payload(total_price, yaml_output, sizeof(yaml_output));
        printf("%s\n", yaml_output);
    }

    return 0;
}