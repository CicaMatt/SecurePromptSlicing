#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_PAYLOAD_SIZE 1024

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL, *quantity_str = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            return "Error parsing YAML payload";
        }

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "product_code")) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event) || event.type != YAML_SCALAR_EVENT) {
                return "Error parsing product_code";
            }
            product_code = (char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "quantity")) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event) || event.type != YAML_SCALAR_EVENT) {
                return "Error parsing quantity";
            }
            quantity_str = (char *)event.data.scalar.value;
            quantity = atoi(quantity_str);
        }

        if (product_code && quantity > 0) break;

        yaml_event_delete(&event);
    }

    if (!strcmp(product_code, "A")) price = 10.0 * quantity;
    else if (!strcmp(product_code, "B")) price = 20.0 * quantity;
    else return "Invalid product code";

    char *total_price = malloc(32);
    sprintf(total_price, "%.2f", price);

    yaml_event_delete(&event);
    yaml_parser_delete(&parser);

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}