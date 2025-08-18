#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.50;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    if (strcmp(product_code, "C789") == 0) return 5.25;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    int i = 0;

    while (yaml_payload[i] != '\0') {
        if (strncmp(&yaml_payload[i], "product_code:", 12) == 0) {
            i += 13;
            order.product_code = &yaml_payload[i];
            while (yaml_payload[i] != '\n' && yaml_payload[i] != '\0') i++;
            order.product_code[i - strlen(order.product_code)] = '\0';
        }
        if (strncmp(&yaml_payload[i], "quantity:", 9) == 0) {
            i += 10;
            sscanf(&yaml_payload[i], "%d", &order.quantity);
            break;
        }
        i++;
    }

    float total_price = get_price_for_product_code(order.product_code) * order.quantity;

    static char response[256];
    sprintf(response, "total_price: %.2f\n", total_price);

    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    printf("%s", calculate_price(yaml_payload));
    return 0;
}