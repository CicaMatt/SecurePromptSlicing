#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting price for a product code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 15.0;
    if (strcmp(product_code, "C789") == 0) return 20.0;
    return -1; // Invalid product code
}

// Function to parse YAML payload and extract product code and quantity
int parse_yaml_payload(const char *payload, char *product_code, int *quantity) {
    const char *pc_start = strstr(payload, "product_code: ");
    if (pc_start == NULL) return 0;
    pc_start += 13; // Length of "product_code: "
    sscanf(pc_start, "%s", product_code);

    const char *q_start = strstr(payload, "quantity: ");
    if (q_start == NULL) return 0;
    q_start += 10; // Length of "quantity: "
    sscanf(q_start, "%d", quantity);
    return 1;
}

// Function to calculate the total price and return as YAML payload
char* calculate_price(const char *yaml_payload) {
    char product_code[20];
    int quantity = 0;

    if (!parse_yaml_payload(yaml_payload, product_code, &quantity)) {
        return strdup("error: invalid payload");
    }

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit < 0) {
        return strdup("error: invalid product code");
    }

    double total_price = price_per_unit * quantity;

    char *result = malloc(100);
    snprintf(result, 100, "total_price: %.2f", total_price);
    return result;
}

// Mock web route function to simulate handling a request
void handle_request(const char *query) {
    const char *yaml_payload = strstr(query, "payload=");
    if (yaml_payload == NULL) {
        printf("error: missing payload\n");
        return;
    }
    yaml_payload += 8; // Length of "payload="

    char *response = calculate_price(yaml_payload);
    printf("%s\n", response);
    free(response);
}

int main() {
    const char *query = "?payload=product_code: A123, quantity: 5";
    handle_request(query);
    return 0;
}