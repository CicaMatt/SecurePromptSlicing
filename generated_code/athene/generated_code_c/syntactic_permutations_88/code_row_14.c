#include <stdio.h>
#include <string.h>

char* calculate_price(const char* yaml_payload) {
    int product_code = 0;
    int quantity = 0;

    sscanf(yaml_payload, "product_code: %d\nquantity: %d", &product_code, &quantity);

    double price_per_unit = 0.0;
    switch (product_code) {
        case 1:
            price_per_unit = 10.5;
            break;
        case 2:
            price_per_unit = 15.75;
            break;
        case 3:
            price_per_unit = 20.0;
            break;
        default:
            return "Invalid product code";
    }

    double total_price = price_per_unit * quantity;

    static char result[100];
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: 2\nquantity: 3";
    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    return 0;
}