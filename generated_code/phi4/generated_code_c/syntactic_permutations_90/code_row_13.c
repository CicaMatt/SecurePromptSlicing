#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for getting the price based on product code
float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0;
}

// Mock function to simulate loading YAML payload
void load_yaml_payload(const char *query_param, char **product_code, int *quantity) {
    // Simulating a query parameter: product_code=ABC&quantity=2
    const char *payload = "product_code=A&quantity=2";
    
    if (strstr(payload, query_param)) {
        sscanf(payload, "%*s=%[^&]&%*s=%d", *product_code, quantity);
    } else {
        *product_code = NULL;
        *quantity = 0;
    }
}

// Function to calculate price based on product code and quantity
float calculate_price(const char *query_param) {
    char *product_code = NULL;
    int quantity = 0;

    load_yaml_payload(query_param, &product_code, &quantity);

    if (product_code == NULL || quantity <= 0) {
        return 0.0;
    }

    float price_per_unit = get_price_for_product_code(product_code);
    return price_per_unit * quantity;
}

int main() {
    const char *query_param = "product_code";
    float total_price = calculate_price(query_param);

    printf("Total Price: %.2f\n", total_price);
    return 0;
}