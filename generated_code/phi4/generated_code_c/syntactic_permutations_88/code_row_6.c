#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a fixed set of products for simplicity.
typedef struct {
    char product_code[10];
    double price;
} Product;

Product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 29.99}
};

int get_product_index(char *product_code) {
    int size = sizeof(products) / sizeof(products[0]);
    for (int i = 0; i < size; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return i;
        }
    }
    return -1;
}

char* calculate_price(char *yaml_payload) {
    static char result[50];
    char *line = strtok(yaml_payload, "\n");
    int quantity = 0;
    char product_code[10] = {0};

    while (line != NULL) {
        if (strncmp(line, "product_code:", 13) == 0) {
            strcpy(product_code, line + 14);
        } else if (strncmp(line, "quantity:", 9) == 0) {
            quantity = atoi(line + 10);
        }
        line = strtok(NULL, "\n");
    }

    int index = get_product_index(product_code);
    if (index != -1 && quantity > 0) {
        double total_price = products[index].price * quantity;
        snprintf(result, sizeof(result), "%.2f", total_price);
    } else {
        strcpy(result, "Invalid product code or quantity");
    }

    return result;
}

int main() {
    char yaml_payload[] =
        "product_code: P001\n"
        "quantity: 3";

    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}