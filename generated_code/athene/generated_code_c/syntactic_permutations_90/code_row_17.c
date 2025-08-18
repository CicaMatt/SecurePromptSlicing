#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

void calculate_price(const char *yaml_payload, char **result) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        exit(1);
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Error parsing YAML\n");
            exit(1);
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_parser_parse(&parser, &event); // Consume key
            product_code = (char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_parser_parse(&parser, &event); // Consume key
            quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) break;
    }

    double total_price = get_price_for_product_code(product_code) * quantity;

    int len = asprintf(result, "total_price: %.2f\n", total_price);
    if (len < 0) {
        fprintf(stderr, "Failed to allocate memory for result\n");
        exit(1);
    }

    yaml_parser_free(&parser);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result;
    calculate_price(yaml_payload, &result);
    printf("%s", result);
    free(result);
    return 0;
}