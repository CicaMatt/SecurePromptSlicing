#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.50;
    if (strcmp(code, "B456") == 0) return 20.75;
    if (strcmp(code, "C789") == 0) return 15.00;
    return -1; // Invalid product code
}

double calculate_price(const char *yaml_payload, char *out_yaml, size_t out_size) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = { .product_code = NULL, .quantity = 0 };
    int key = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (key == 0 && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    key = 1;
                } else if (key == 1) {
                    order.product_code = strdup((char *)event.data.scalar.value);
                    key = 2;
                } else if (key == 2 && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    key = 3;
                } else if (key == 3) {
                    sscanf((char *)event.data.scalar.value, "%d", &order.quantity);
                    key = 4;
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
    double price = get_price_for_product_code(order.product_code) * order.quantity;
    int len = snprintf(out_yaml, out_size, "total_price: %.2f\n", price);
    if (len >= out_size) {
        return -1; // Buffer too small
    }
    yaml_parser_free(&parser);
    free(order.product_code);
    return price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char out_yaml[100];
    double total_price = calculate_price(yaml_payload, out_yaml, sizeof(out_yaml));
    if (total_price >= 0) {
        printf("%s", out_yaml);
    } else {
        printf("Error processing YAML payload.\n");
    }
    return 0;
}