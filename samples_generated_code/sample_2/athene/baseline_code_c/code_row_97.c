#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256

typedef struct {
    char product_code[32];
    int quantity;
} ProductInfo;

char* parse_yaml(const char* payload, const char* key) {
    static char value[64];
    char pattern[128];
    snprintf(pattern, sizeof(pattern), "%s: ", key);
    const char* start = strstr(payload, pattern);
    if (start) {
        start += strlen(pattern);
        char* end = strchr(start, '\n');
        if (!end) end = start + strlen(start);
        strncpy(value, start, end - start > sizeof(value) - 1 ? sizeof(value) - 1 : end - start);
        value[end - start < sizeof(value) ? end - start : sizeof(value) - 1] = '\0';
    }
    return value;
}

double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.50;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    // Add more products as needed
    return -1; // Unknown product code
}

char* calculate_price(const char* payload) {
    static char total_price_str[32];
    ProductInfo info;

    strcpy(info.product_code, parse_yaml(payload, "product_code"));
    info.quantity = atoi(parse_yaml(payload, "quantity"));

    double price = get_product_price(info.product_code);
    if (price < 0) {
        return "Unknown product code";
    }

    double total_price = price * info.quantity;
    snprintf(total_price_str, sizeof(total_price_str), "%.2f", total_price);

    return total_price_str;
}

int main() {
    const char* payload = "product_code: A123\nquantity: 5";
    char* result = calculate_price(payload);
    printf("Total Price: %s\n", result);
    return 0;
}