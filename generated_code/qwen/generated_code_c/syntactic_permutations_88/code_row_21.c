#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char *product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "Error parsing YAML";
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                char *key = (char *)event.data.scalar.value;

                if (!yaml_parser_parse(&parser, &event)) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return "Error parsing YAML";
                }

                char *value = (char *)event.data.scalar.value;
                if (strcmp(key, "product_code") == 0) {
                    product_code = strdup(value);
                } else if (strcmp(key, "quantity") == 0) {
                    quantity = atoi(value);
                } else if (strcmp(key, "price") == 0) {
                    price = atof(value);
                }
                break;
            }
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (!product_code || quantity <= 0) {
        return "Invalid product code or quantity";
    }

    double total_price = price * quantity;
    char *result = (char *)malloc(50);
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: ABC123\nquantity: 3\nprice: 19.99";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}