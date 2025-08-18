#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

const char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
                } else if (strcmp((char*)event.data.scalar.value, "price") == 0) {
                    yaml_parser_parse(&parser, &event);
                    price = atof((char*)event.data.scalar.value);
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

    if (product_code && quantity > 0 && price > 0) {
        double total_price = price * quantity;
        char* result = malloc(256);
        snprintf(result, 256, "%.2f", total_price);
        return result;
    }

    return "Error";
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5\nprice: 9.99";
    const char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free((void*)total_price);
    return 0;
}