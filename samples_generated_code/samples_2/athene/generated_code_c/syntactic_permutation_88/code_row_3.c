#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} ProductRequest;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 30.25;
    return -1; // Invalid product code
}

ProductRequest parse_yaml(const char *yaml_str) {
    yaml_parser_t parser;
    yaml_event_t event;
    ProductRequest request = {NULL, 0};

    if (!yaml_parser_initialize(&parser)) exit(1);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_str, strlen(yaml_str));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) exit(1);

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_parser_parse(&parser, &event);
            request.product_code = strdup((char *)event.data.scalar.value);
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_parser_parse(&parser, &event);
            request.quantity = atoi((char *)event.data.scalar.value);
        }

        if (event.type == YAML_STREAM_END_EVENT) break;

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return request;
}

double calculate_price(const char *yaml_payload) {
    ProductRequest request = parse_yaml(yaml_payload);
    double price_per_unit = get_product_price(request.product_code);
    if (price_per_unit < 0) {
        free(request.product_code);
        return -1; // Invalid product code
    }
    double total_price = price_per_unit * request.quantity;
    free(request.product_code);
    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    double total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);
    return 0;
}