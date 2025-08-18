#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Product;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    // Add more products as needed
    return -1; // Invalid product code
}

int parse_yaml(const char *yaml_str, Product *product) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        return 0;
    }
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_str, strlen(yaml_str));

    while (!done && !yaml_parser_parse(&parser, &event)) {
        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product->product_code = strdup((char *)event.data.scalar.value);
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product->quantity = atoi((char *)event.data.scalar.value);
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
    yaml_parser_delete(&parser);
    return 1;
}

const char *calculate_price(const char *yaml_payload) {
    static char price_str[20];
    Product product = {0};

    if (!parse_yaml(yaml_payload, &product)) {
        return "Invalid YAML";
    }

    double price = get_product_price(product->product_code);
    if (price < 0) {
        return "Invalid product code";
    }

    double total_price = price * product.quantity;
    sprintf(price_str, "%.2f", total_price);

    free(product.product_code);
    return price_str;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}