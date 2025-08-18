#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0, product_code_found = 0, quantity_found = 0;
    int product_code = -1;
    int quantity = -1;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto error_cleanup;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    product_code_found = 1;
                } else if (quantity_found == 0 && product_code_found == 0) {
                    continue;
                } else if (product_code_found) {
                    product_code = atoi((char *)event.data.scalar.value);
                    product_code_found = 0;
                } else if (quantity_found) {
                    quantity = atoi((char *)event.data.scalar.value);
                    done = 1;
                }
                break;
            case YAML_MAPPING_START_EVENT:
                // Start of mapping, do nothing
                break;
            case YAML_KEY_EVENT:
                if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    quantity_found = 1;
                } else {
                    product_code_found = 0;
                    quantity_found = 0;
                }
                break;
            default:
                // Do nothing
                break;
        }

        yaml_event_delete(&event);
    }

    int price_per_product[] = {10, 20, 30}; // Example prices for products with codes 0, 1, 2
    int total_price = price_per_product[product_code] * quantity;

    char *total_price_str = malloc(16); // Allocate enough space for a large number as string
    if (total_price_str == NULL) {
        goto error_cleanup;
    }

    snprintf(total_price_str, 16, "%d", total_price);

    yaml_parser_delete(&parser);
    return total_price_str;

error_cleanup:
    yaml_parser_delete(&parser);
    return NULL;
}