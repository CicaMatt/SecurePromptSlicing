#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

#define MAX_DOC_SIZE 1024

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    const char* code = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Failed to initialize parser");
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            done = 1;
        } else {
            switch(event.type) {
                case YAML_SCALAR_EVENT:
                    if (strcmp((char*)event.data.scalar.value, "_code") == 0) {
                        yaml_parser_parse(&parser, &event);
                        code = (const char*)event.data.scalar.value;
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
        }
    }

    yaml_event_delete(&event);
    yaml_parser_delete(&parser);

    if (code && quantity > 0) {
        double total_price = price * quantity;
        char* result = malloc(32);
        sprintf(result, "%.2f", total_price);
        return result;
    } else {
        return strdup("Invalid input");
    }
}

int main() {
    const char* yaml_input = "_code: ABC123\nquantity: 5\nprice: 9.99";
    char* result = calculate_price(yaml_input);
    printf("Total Price: %s\n", result);
    free(result);
    return 0;
}