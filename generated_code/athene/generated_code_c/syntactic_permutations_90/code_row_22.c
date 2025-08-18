#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    double price;
} Product;

double get_price_for_product_code(const char *product_code) {
    // Example product codes and prices
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 15.0;
    return -1; // Product code not found
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    double total_price = 0.0;

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
            yaml_event_t value_event;
            if (!yaml_parser_parse(&parser, &value_event)) {
                fprintf(stderr, "Error parsing YAML\n");
                exit(1);
            }
            if (value_event.type == YAML_SCALAR_EVENT) {
                double price = get_price_for_product_code((char *)value_event.data.scalar.value);
                if (price >= 0) {
                    total_price += price;
                } else {
                    fprintf(stderr, "Unknown product code: %s\n", (char *)value_event.data.scalar.value);
                }
            }
            yaml_event_delete(&value_event);
        }

        if (event.type == YAML_STREAM_END_EVENT) break;

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return total_price;
}

void generate_yaml_response(double total_price, char *response, size_t response_size) {
    snprintf(response, response_size, "total_price: %.2f", total_price);
}

int main() {
    const char *yaml_payload = "- product_code: A123\n- product_code: B456";
    double total_price = calculate_price(yaml_payload);

    char yaml_response[100];
    generate_yaml_response(total_price, yaml_response, sizeof(yaml_response));

    printf("%s\n", yaml_response);
    return 0;
}