#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} ProductInfo;

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    ProductInfo product_info = {0};
    double price_per_unit = 10.0; // Example fixed price per unit

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto cleanup;
        }

        if (event.type == YAML_SCALAR_EVENT && product_info.product_code == NULL) {
            if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                yaml_event_delete(&event);
                if (!yaml_parser_parse(&parser, &event)) {
                    goto cleanup;
                }
                if (event.type != YAML_SCALAR_EVENT) {
                    goto cleanup;
                }
                product_info.product_code = strdup((char *)event.data.scalar.value);
            } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                yaml_event_delete(&event);
                if (!yaml_parser_parse(&parser, &event)) {
                    goto cleanup;
                }
                if (event.type != YAML_SCALAR_EVENT) {
                    goto cleanup;
                }
                product_info.quantity = atoi((char *)event.data.scalar.value);
            }
        }

        if (product_info.product_code && product_info.quantity) {
            break;
        }

        yaml_event_delete(&event);
    }

    double total_price = price_per_unit * product_info.quantity;
    char *price_str = malloc(20); // Allocate enough space for the price string
    sprintf(price_str, "%.2f", total_price);

cleanup:
    if (product_info.product_code) {
        free(product_info.product_code);
    }
    yaml_parser_delete(&parser);
    return price_str;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    if (price) {
        printf("Total Price: %s\n", price);
        free(price);
    }
    return 0;
}