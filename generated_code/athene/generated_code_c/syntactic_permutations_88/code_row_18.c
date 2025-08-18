#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Product;

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            const char *value = (const char *)event.data.scalar.value;

            if (strcmp((char *)event.data.scalar.tag, "tag:yaml.org,2002:str") == 0 &&
                strcmp(value, "product_code") == 0) {
                yaml_parser_parse(&parser, &event);
                product_code = (const char *)event.data.scalar.value;
            } else if (strcmp((char *)event.data.scalar.tag, "tag:yaml.org,2002:int") == 0 &&
                       strcmp(value, "quantity") == 0) {
                yaml_parser_parse(&parser, &event);
                quantity = atoi((const char *)event.data.scalar.value);
            }
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_free(&parser);

    if (!product_code || quantity <= 0) {
        return -1;
    }

    // Example pricing logic
    if (strcmp(product_code, "A") == 0) {
        price = 10.0 * quantity;
    } else if (strcmp(product_code, "B") == 0) {
        price = 20.0 * quantity;
    } else {
        return -1;
    }

    return price;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 5";
    double price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", price);
    return 0;
}