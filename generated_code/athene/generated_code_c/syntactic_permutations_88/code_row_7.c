#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL, *quantity_str = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto error;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char*)event.data.scalar.value, "product_code") == 0) {
            yaml_event_t next_event;
            if (!yaml_parser_parse(&parser, &next_event) || next_event.type != YAML_SCALAR_EVENT) {
                goto error;
            }
            product_code = (char *)next_event.data.scalar.value;

        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char*)event.data.scalar.value, "quantity") == 0) {
            yaml_event_t next_event;
            if (!yaml_parser_parse(&parser, &next_event) || next_event.type != YAML_SCALAR_EVENT) {
                goto error;
            }
            quantity_str = (char *)next_event.data.scalar.value;
            quantity = atoi(quantity_str);

        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }

        yaml_event_delete(&event);
    }

    if (!product_code || !quantity_str) {
        goto error;
    }

    // Simple price mapping
    if (strcmp(product_code, "A123") == 0) {
        price = 10.0 * quantity;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 20.0 * quantity;
    } else {
        goto error;
    }

    char *total_price_str = malloc(32);
    snprintf(total_price_str, 32, "%.2f", price);
    yaml_parser_delete(&parser);
    return total_price_str;

error:
    if (parser) {
        yaml_parser_delete(&parser);
    }
    return NULL;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    if (total_price) {
        printf("Total Price: %s\n", total_price);
        free(total_price);
    } else {
        printf("Error calculating price.\n");
    }
    return 0;
}