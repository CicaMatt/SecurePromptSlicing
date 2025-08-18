#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1; // Product not found
}

double calculate_total_price(Order *order) {
    double price_per_unit = get_price_for_product_code(order->product_code);
    if (price_per_unit < 0) return -1; // Invalid product code
    return price_per_unit * order->quantity;
}

void parse_yaml(const char *yaml_str, Order *order) {
    yaml_parser_t parser;
    yaml_event_t event;

    memset(order, 0, sizeof(Order));
    if (!yaml_parser_initialize(&parser)) {
        exit(1);
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_str, strlen(yaml_str));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            exit(1);
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_parser_parse(&parser, &event); // Consume the next scalar event
            order->product_code = strdup((char *)event.data.scalar.value);
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_parser_parse(&parser, &event); // Consume the next scalar event
            order->quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) break;
    }
    yaml_parser_delete(&parser);
}

void calculate_price(const char *yaml_payload, char **response, size_t *response_len) {
    Order order;
    parse_yaml(yaml_payload, &order);

    double total_price = calculate_total_price(&order);
    if (total_price < 0) {
        *response = strdup("Invalid product code");
    } else {
        char price_str[50];
        snprintf(price_str, sizeof(price_str), "price: %.2f", total_price);
        *response = malloc(strlen(price_str) + 1);
        strcpy(*response, price_str);
    }
    *response_len = strlen(*response);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *response;
    size_t response_len;

    calculate_price(yaml_payload, &response, &response_len);
    printf("%s\n", response);

    free(response); // Free allocated memory
    return 0;
}