#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Failed to initialize YAML parser");
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0;
    int quantity_found = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch(event.type) {
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
    }

    yaml_parser_delete(&parser);

    float price = 0.0;
    if (product_code) {
        // Assuming a simple price mapping for demonstration
        if (strcmp(product_code, "A123") == 0) {
            price = 9.99;
        } else if (strcmp(product_code, "B456") == 0) {
            price = 14.99;
        }
        free((char*)product_code);
    }

    float total_price = price * quantity;

    char* result = malloc(20);
    snprintf(result, 20, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 5";
    char* price = calculate_price(yaml_input);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}