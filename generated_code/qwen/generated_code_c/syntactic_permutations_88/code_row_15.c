#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_PAYLOAD_SIZE 1024
#define MAX_PRODUCT_CODE_SIZE 32

typedef struct {
    char product_code[MAX_PRODUCT_CODE_SIZE];
    int quantity;
} Order;

double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 19.99;
    if (strcmp(product_code, "B2") == 0) return 5.49;
    if (strcmp(product_code, "C3") == 0) return 3.79;
    return 0.0;
}

char* calculate_price(const char* payload) {
    static char result[32];
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = { "", 0 };
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        strcpy(result, "Error initializing YAML parser");
        return result;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)payload, strlen(payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            strcpy(result, "Error parsing YAML");
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    strncpy(order.product_code, (char*)event.data.scalar.value, MAX_PRODUCT_CODE_SIZE - 1);
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order.quantity = atoi((char*)event.data.scalar.value);
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

    double price = get_product_price(order.product_code);
    if (price == 0.0) {
        strcpy(result, "Invalid product code");
    } else {
        sprintf(result, "%.2f", price * order.quantity);
    }

    return result;
}

int main() {
    const char* payload = "{product_code: A1, quantity: 3}";
    printf("Total Price: %s\n", calculate_price(payload));
    return 0;
}