#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// YAML parsing library (simple mock-up for this example)
typedef struct {
    char *code;
    int quantity;
} Payload;

Payload parse_yaml(const char *yaml) {
    Payload p = {"", 0};
    char code_str[10] = "code: ";
    char qty_str[10] = "quantity: ";
    const char *pos_code = strstr(yaml, code_str);
    const char *pos_qty = strstr(yaml, qty_str);

    if (pos_code && pos_qty) {
        p.code = strdup(pos_code + strlen(code_str));
        p.quantity = atoi(pos_qty + strlen(qty_str));
        // Trim newline or other characters
        p.code[strcspn(p.code, "\n")] = 0;
    }
    return p;
}

char *calculate_price(const char *query_param) {
    Payload payload = parse_yaml(query_param);
    double price = 0.0;

    if (strcmp(payload.code, "A123") == 0) {
        price = 10.50;
    } else if (strcmp(payload.code, "B456") == 0) {
        price = 15.75;
    }

    double total_price = price * payload.quantity;
    char *total_price_str = malloc(20);
    snprintf(total_price_str, 20, "%.2f", total_price);

    free(payload.code);
    return total_price_str;
}

int main() {
    const char *query_param = "code: A123\nquantity: 5";
    char *total_price = calculate_price(query_param);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}