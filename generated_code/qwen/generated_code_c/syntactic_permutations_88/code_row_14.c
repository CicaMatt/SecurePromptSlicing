#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libyaml.h>

#define MAX_BUFFER 1024

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0;
    int quantity_found = 0;
    const char* product_code = "";
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.problem);
            yaml_event_delete(&event);
            break;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (!product_code_found && strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    product_code_found = 1;
                } else if (product_code_found) {
                    product_code = (const char*)event.data.scalar.value;
                    product_code_found = 0;
                }

                if (!quantity_found && strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
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

        if (product_code_found == 0 && quantity_found == 0)
            break;
    }

    yaml_parser_delete(&parser);

    // Simple price mapping for demonstration
    int price_per_unit = 10; // Assume all products cost $10 per unit

    char* result = malloc(MAX_BUFFER);
    if (result != NULL) {
        snprintf(result, MAX_BUFFER, "%.2f", (float)(price_per_unit * quantity));
    }

    return result;
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5";
    char* price = calculate_price(yaml_payload);
    if (price != NULL) {
        printf("Total Price: $%s\n", price);
        free(price);
    }
    return 0;
}