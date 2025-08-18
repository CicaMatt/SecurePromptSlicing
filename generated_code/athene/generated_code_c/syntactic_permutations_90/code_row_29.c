#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1; // Product code not found
}

char* calculate_price(const char *yaml_payload, size_t *out_len) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) return NULL;
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event) || event.type != YAML_SCALAR_EVENT) break;
            product_code = (char *)event.data.scalar.value;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event) || event.type != YAML_SCALAR_EVENT) break;
            quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (product_code == NULL || quantity <= 0) return NULL;

    double total_price = get_price_for_product_code(product_code) * quantity;
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);

    *out_len = strlen(buffer);
    char *result = malloc(*out_len + 1);
    if (result != NULL) {
        strcpy(result, buffer);
    }

    return result;
}