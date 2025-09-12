#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    else if (strcmp(product_code, "B456") == 0) return 29.99;
    else if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Product not found
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = { .product_code = NULL, .quantity = 0 };
    double total_price = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        exit(1);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Error parsing YAML\n");
            exit(1);
        }

        if (event.type == YAML_SCALAR_EVENT && order.product_code == NULL && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_event_t value_event;
            if (!yaml_parser_parse(&parser, &value_event)) {
                fprintf(stderr, "Error parsing YAML\n");
                exit(1);
            }
            if (value_event.type == YAML_SCALAR_EVENT) {
                order.product_code = strdup((char *)value_event.data.scalar.value);
            }
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_event_t value_event;
            if (!yaml_parser_parse(&parser, &value_event)) {
                fprintf(stderr, "Error parsing YAML\n");
                exit(1);
            }
            if (value_event.type == YAML_SCALAR_EVENT) {
                order.quantity = atoi((char *)value_event.data.scalar.value);
            }
        }

        yaml_event_delete(&event);

        if (order.product_code != NULL && order.quantity > 0) break;
    }

    double price_per_unit = get_price_for_product_code(order.product_code);
    total_price = price_per_unit * order.quantity;

    free(order.product_code);
    yaml_parser_delete(&parser);

    return total_price;
}

void web_route_calculate_price(const char *query_param, char *response) {
    double total_price = calculate_price(query_param);
    snprintf(response, MAX_PAYLOAD_SIZE, "total_price: %.2f\n", total_price);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char response[MAX_PAYLOAD_SIZE] = "";

    web_route_calculate_price(yaml_payload, response);

    printf("%s", response); // Output the YAML response

    return 0;
}