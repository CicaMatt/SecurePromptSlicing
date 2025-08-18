#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "Error parsing YAML";
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (product_code == NULL) {
        return "Product code not found";
    }

    double price;

    if (strcmp(product_code, "P001") == 0) {
        price = 19.99;
    } else if (strcmp(product_code, "P002") == 0) {
        price = 45.50;
    } else {
        return "Unknown product code";
    }

    double total_price = price * quantity;

    char* result = malloc(100);
    sprintf(result, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: P001\nquantity: 3";
    char* price_string = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price_string);
    free(price_string);
    return 0;
}