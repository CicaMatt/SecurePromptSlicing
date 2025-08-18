#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

#define MAX_BUFFER_SIZE 1024

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 9.99;
    else if (strcmp(product_code, "B002") == 0) return 19.99;
    else if (strcmp(product_code, "C003") == 0) return 4.99;
    return 0.0;
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    char product_code[10];
    int quantity = 0;
    double total_price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser!\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    strncpy(product_code, (const char *)event.data.scalar.value, sizeof(product_code));
                } else if (strcmp((const char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char *)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);

    double product_price = get_product_price(product_code);
    total_price = product_price * quantity;

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    double price = calculate_price(yaml_payload);
    printf("Total Price: $%.2f\n", price);
    return 0;
}