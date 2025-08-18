#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the YAML parser\n");
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    double price = 0.0;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "price") == 0) {
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
    char* result = (char*)malloc(20);
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product:\n  price: 19.99\n  quantity: 3";
    char* total_price = calculate_price(yaml_payload);
    if (total_price) {
        printf("Total Price: %s\n", total_price);
        free(total_price);
    }
    return 0;
}