#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "price") == 0) {
                    yaml_parser_parse(&parser, &event);
                    price = atof((const char*)event.data.scalar.value);
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
    char* result = malloc(50); // Allocate enough space for the result string
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5\nprice: 9.99";
    char* total_price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price_str);
    free(total_price_str);
    return 0;
}