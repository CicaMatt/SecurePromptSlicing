#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser (dummy implementation for this example)
typedef struct {
    char *product_code;
    int quantity;
} YamlPayload;

YamlPayload parse_yaml(const char *yaml) {
    YamlPayload payload = {"", 0};
    char *token, *rest = strdup(yaml);

    token = strtok(rest, " :\n");
    if (strcmp(token, "product_code") == 0) {
        token = strtok(NULL, " :\n");
        if (token) {
            payload.product_code = strdup(token);
        }
    }

    token = strtok(NULL, " :\n");
    if (strcmp(token, "quantity") == 0) {
        token = strtok(NULL, " :\n");
        if (token) {
            payload.quantity = atoi(token);
        }
    }

    free(rest);
    return payload;
}

// Price table
const double prices[] = {
    [123] = 9.99,
    [456] = 19.99,
    [789] = 29.99
};

char *calculate_price(const char *yaml) {
    YamlPayload payload = parse_yaml(yaml);
    double price = prices[atoi(payload.product_code)];
    double total_price = price * payload.quantity;

    char *result = malloc(100); // Allocate enough space for the result
    if (result == NULL) return NULL;
    sprintf(result, "%.2f", total_price);

    free(payload.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: 123\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    if (total_price) {
        printf("Total Price: %s\n", total_price);
        free(total_price);
    }
    return 0;
}