#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_PAYLOAD_SIZE 1024

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return -1.0; // Invalid product code
}

void calculate_price(const char *yaml_payload, char **result, size_t *result_size) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (!yaml_parser_check_eof(&parser)) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT) {
            const char *value = (const char *)event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (strcmp(value, "product_code") == 0) {
                yaml_parser_parse(&parser, &event);
                product_code = (const char *)event.data.scalar.value;
            } else if (strcmp(value, "quantity") == 0) {
                yaml_parser_parse(&parser, &event);
                quantity = atoi((const char *)event.data.scalar.value);
            }
        }

        yaml_event_delete(&event);
    }

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    int result_len = asprintf(result, "total_price: %.2f", total_price);
    if (result_len < 0) {
        *result = NULL;
    }
    *result_size = result_len + 1;
    yaml_parser_delete(&parser);
}

int main() {
    char *yaml_payload = "product_code: A\nquantity: 5";
    char *result;
    size_t result_size;

    calculate_price(yaml_payload, &result, &result_size);

    if (result) {
        printf("%.*s\n", (int)result_size - 1, result);
        free(result);
    }

    return 0;
}