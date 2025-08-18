#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Product code not found
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    char product_code[256] = {0};
    int quantity = 0;
    double total_price = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    strncpy(product_code, (char *)event.data.scalar.value, sizeof(product_code));
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto end;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

end:
    yaml_event_delete(&event);
    yaml_parser_delete(&parser);

    if (quantity > 0) {
        double price = get_price_for_product_code(product_code);
        if (price != -1) {
            total_price = price * quantity;
            char *result_yaml = malloc(256);
            snprintf(result_yaml, 256, "total_price: %.2f\n", total_price);
            return result_yaml;
        }
    }

    return strdup("error: invalid product code or quantity");
}

int main() {
    const char *yaml_input = "product_code: A123\nquantity: 2";
    char *result = calculate_price(yaml_input);

    if (result) {
        printf("%s", result);
        free(result);
    }

    return 0;
}