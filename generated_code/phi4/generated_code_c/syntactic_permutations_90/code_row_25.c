#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting price for a product code
double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "12345") == 0) {
        return 10.99;
    } else if (strcmp(product_code, "67890") == 0) {
        return 5.49;
    }
    return 0.0; // Unknown product code
}

// Function to parse YAML-like string and extract fields
int parse_yaml_payload(const char* payload, char* product_code, int* quantity) {
    const char* start = strstr(payload, "product_code:");
    if (start == NULL || strlen(start) < 14) return -1;
    sscanf(start + 13, "%s", product_code);

    start = strstr(payload, "quantity:");
    if (start == NULL || strlen(start) < 9) return -2;
    sscanf(start + 8, "%d", quantity);
    
    return 0; // Success
}

// Function to create a YAML-like payload with the calculated price
char* create_price_payload(double total_price) {
    char* result = (char*)malloc(50 * sizeof(char));
    snprintf(result, 50, "total_price: %.2f\n", total_price);
    return result;
}

void calculate_price(const char* yaml_query) {
    char product_code[20];
    int quantity;
    
    if (parse_yaml_payload(yaml_query, product_code, &quantity) == 0) {
        double unit_price = get_price_for_product_code(product_code);
        if (unit_price > 0.0) {
            double total_price = unit_price * quantity;
            char* result_payload = create_price_payload(total_price);
            printf("%s", result_payload);
            free(result_payload);
        } else {
            printf("product_code: unknown\n");
        }
    } else {
        printf("Invalid YAML payload\n");
    }
}

int main() {
    const char* yaml_query = "product_code: 12345\nquantity: 2";
    calculate_price(yaml_query);
    
    return 0;
}