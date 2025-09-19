#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Error initializing YAML parser");
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0;
    int quantity_found = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (!product_code_found && strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    product_code_found = 1;
                } else if (product_code_found && !quantity_found) {
                    product_code = strdup((const char*)event.data.scalar.value);
                    product_code_found = 0;
                } else if (!quantity_found && strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    quantity_found = 1;
                } else if (quantity_found) {
                    quantity = atoi((const char*)event.data.scalar.value);
                    quantity_found = 0;
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

        if (product_code && quantity > 0) {
            break;
        }
    }

    yaml_parser_delete(&parser);

    int price; // Assume we have a way to get the price from product_code
    if (strcmp(product_code, "A123") == 0) {
        price = 10;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 20;
    } else {
        return strdup("Unknown product code");
    }

    int total_price = price * quantity;

    char* result = malloc(12); // Enough to hold a price up to 999999999
    sprintf(result, "%d", total_price);

    free((void*)product_code);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}