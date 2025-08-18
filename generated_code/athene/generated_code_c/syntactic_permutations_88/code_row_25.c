#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} ProductInfo;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    static char price_str[50];
    ProductInfo info = {"", 0};
    int index = 0;

    while (index < strlen(yaml_payload)) {
        if (strncmp(yaml_payload + index, "product_code:", 12) == 0) {
            sscanf(yaml_payload + index + 13, "%[^:]", info.product_code);
        } else if (strncmp(yaml_payload + index, "quantity:", 9) == 0) {
            sscanf(yaml_payload + index + 10, "%d", &info.quantity);
        }
        while (yaml_payload[index] != '\n' && index < strlen(yaml_payload)) index++;
        index++;
    }

    double price = get_product_price(info.product_code) * info.quantity;
    sprintf(price_str, "%.2f", price);
    return price_str;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    printf("Price: %s\n", price);
    return 0;
}