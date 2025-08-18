#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_BUFFER_SIZE 1024

const char* get_value(yaml_parser_t *parser, const char *key) {
    yaml_event_t event;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(parser, &event)) {
            return NULL;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, key) == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(parser, &event)) {
                        return NULL;
                    }
                    const char *value = (const char *)event.data.scalar.value;
                    yaml_event_delete(&event);
                    return value;
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

    return NULL;
}

char* calculate_price(const char *yaml_payload) {
    static char result[50];
    yaml_parser_t parser;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    const char *product_code = get_value(&parser, "product_code");
    const char *quantity_str = get_value(&parser, "quantity");

    yaml_parser_delete(&parser);

    if (!product_code || !quantity_str) {
        return "Invalid YAML payload";
    }

    int quantity = atoi(quantity_str);
    float price;

    // Simple product pricing logic
    if (strcmp(product_code, "A123") == 0) {
        price = 19.99;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 29.99;
    } else {
        return "Unknown product code";
    }

    float total_price = price * quantity;
    snprintf(result, sizeof(result), "%.2f", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 3";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}