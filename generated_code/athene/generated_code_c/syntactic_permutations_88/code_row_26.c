#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    if (strcmp(product_code, "C789") == 0) return 5.25;
    return -1; // Invalid product code
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

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

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event); // Consume the next scalar
                    product_code = (const char *)event.data.scalar.value;
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event); // Consume the next scalar
                    quantity = atoi((const char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto done;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

done:
    yaml_parser_cleanup(&parser);

    if (product_code == NULL || quantity <= 0) {
        return -1; // Invalid input
    }

    double price = get_product_price(product_code);
    if (price < 0) {
        return -1; // Invalid product code
    }

    return price * quantity;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    double total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);
    return 0;
}