#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libyaml/yaml.h>

#define MAX_BUFFER_SIZE 1024

const char* get_value(yaml_parser_t *parser, const char *key) {
    yaml_event_t event;
    while (1) {
        if (!yaml_parser_parse(parser, &event)) {
            break;
        }
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, key) == 0) {
            yaml_parser_parse(parser, &event);
            const char *value = (const char *)event.data.scalar.value;
            yaml_event_delete(&event);
            return value;
        }
        yaml_event_delete(&event);
    }
    return NULL;
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    const char *product_code = get_value(&parser, "product_code");
    const char *quantity_str = get_value(&parser, "quantity");

    yaml_parser_delete(&parser);

    if (!product_code || !quantity_str) {
        return strdup("Invalid payload");
    }

    int quantity = atoi(quantity_str);
    double price = 0.0;

    // Example prices for demonstration
    if (strcmp(product_code, "A123") == 0) {
        price = 9.99;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 19.99;
    }

    double total_price = price * quantity;
    char *result = malloc(20);
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}