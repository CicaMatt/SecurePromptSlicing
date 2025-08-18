#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

const char* get_value(yaml_parser_t *parser, const char *key) {
    yaml_event_t event;
    while (1) {
        if (!yaml_parser_parse(parser, &event)) {
            return NULL;
        }
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, key) == 0) {
            yaml_parser_parse(parser, &event);
            const char *value = (const char *)event.data.scalar.value;
            yaml_event_delete(&event);
            return value;
        }
        yaml_event_delete(&event);
    }
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    const char *product_code = get_value(&parser, "product_code");
    const char *quantity_str = get_value(&parser, "quantity");

    yaml_parser_delete(&parser);

    if (!product_code || !quantity_str) {
        return NULL;
    }

    int quantity = atoi(quantity_str);
    float price = 0.0;

    if (strcmp(product_code, "P1") == 0) {
        price = 9.99;
    } else if (strcmp(product_code, "P2") == 0) {
        price = 14.99;
    } else {
        return NULL;
    }

    float total_price = price * quantity;

    char *result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: P1\nquantity: 3";
    char *total_price = calculate_price(yaml_payload);
    if (total_price) {
        printf("Total Price: %s\n", total_price);
        free(total_price);
    } else {
        printf("Failed to calculate price.\n");
    }
    return 0;
}