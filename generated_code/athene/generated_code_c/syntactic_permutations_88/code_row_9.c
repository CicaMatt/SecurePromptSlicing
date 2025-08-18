#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return "Error parsing YAML";
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_parser_parse(&parser, &event); // Skip key
            product_code = (const char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_parser_parse(&parser, &event); // Skip key
            quantity = atoi((const char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (product_code != NULL && quantity > 0) break;
    }

    int price = 0;

    if (strcmp(product_code, "A123") == 0) {
        price = 10 * quantity;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 20 * quantity;
    }

    char *total_price_str = malloc(16);
    snprintf(total_price_str, 16, "%d", price);

    yaml_parser_free(&parser);

    return total_price_str;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}