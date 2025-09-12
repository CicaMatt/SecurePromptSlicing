#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_name = NULL;
    double price = 0.0;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "Error parsing YAML";
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_name") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_name = (const char*)event.data.scalar.value;
                } else if (strcmp((const char*)event.data.scalar.value, "price") == 0) {
                    yaml_parser_parse(&parser, &event);
                    price = atof((const char*)event.data.scalar.value);
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

    double total_price = price * quantity;
    char* result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product_name: example_product\nprice: 19.99\nquantity: 3";
    char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}