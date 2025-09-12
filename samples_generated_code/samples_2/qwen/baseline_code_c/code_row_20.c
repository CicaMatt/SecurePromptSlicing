#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 5.49;
    if (strcmp(product_code, "C789") == 0) return 3.99;
    return 0.0; // Default price for unknown product codes
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    char* product_code = NULL;
    int quantity = 0;
    double total_price = 0.0;

    if (!yaml_parser_initialize(&parser)) return strdup("error: Cannot initialize the parser");

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return strdup("error: Parser error");
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = strdup((const char*)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);

    if (product_code && quantity > 0) {
        total_price = get_price_for_product_code(product_code) * quantity;
        char* result = malloc(100);
        snprintf(result, 99, "total_price: %.2f", total_price);
        free(product_code);
        return result;
    }

    return strdup("error: Invalid input");
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char* response = calculate_price(yaml_payload);
    printf("%s\n", response);
    free(response);
    return 0;
}