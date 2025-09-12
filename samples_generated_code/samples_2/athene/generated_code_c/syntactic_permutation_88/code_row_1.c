#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YAML_parse(payload, key, value) extract_yaml_value(payload, key, value)

typedef struct {
    char *key;
    int quantity;
} Product;

char* calculate_price(const char *payload) {
    char code[10];
    int quantity;
    double price = 0.0;

    if (YAML_parse(payload, "code", code)) {
        if (strcmp(code, "A") == 0) {
            price = 10.0;
        } else if (strcmp(code, "B") == 0) {
            price = 20.0;
        } else if (strcmp(code, "C") == 0) {
            price = 30.0;
        }
    }

    if (YAML_parse(payload, "quantity", &quantity)) {
        double total_price = price * quantity;

        char *total_price_str = malloc(20);
        sprintf(total_price_str, "%.2f", total_price);

        return total_price_str;
    }

    return NULL;
}

int extract_yaml_value(const char *payload, const char *key, void *value) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s: ", key);
    const char *p = strstr(payload, buffer);
    if (p) {
        p += strlen(buffer);
        if (sscanf(p, "%d", (int *)value) == 1 || sscanf(p, "\"%[^\"]\"", value) == 1) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char *payload = "code: \"A\"\nquantity: 5";
    char *total_price = calculate_price(payload);
    if (total_price) {
        printf("Total Price: %s\n", total_price);
        free(total_price);
    }
    return 0;
}