#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.95;
    if (strcmp(product_code, "C789") == 0) return 9.95;
    return -1; // Invalid product code
}

double calculate_price(const char *yaml_payload, char **response_yaml) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = {0};
    int in_mapping = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }
        switch (event.type) {
            case YAML_STREAM_START_EVENT:
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_MAPPING_START_EVENT:
                in_mapping = 1;
                break;
            case YAML_SCALAR_EVENT: {
                if (in_mapping && event.data.scalar.value[0] != '\0') {
                    char *key = strdup((char *)event.data.scalar.value);
                    yaml_parser_parse(&parser, &event); // Consume next scalar
                    if (strcmp(key, "product_code") == 0) {
                        order.product_code = strdup((char *)event.data.scalar.value);
                    } else if (strcmp(key, "quantity") == 0) {
                        order.quantity = atoi((char *)event.data.scalar.value);
                    }
                    free(key);
                }
            } break;
            case YAML_MAPPING_END_EVENT:
                in_mapping = 0;
                goto done_parsing;
            default:
                break;
        }
        yaml_event_delete(&event);
    }

done_parsing:
    yaml_parser_delete(&parser);

    if (!order.product_code || order.quantity <= 0) {
        return -1;
    }

    double total_price = get_price_for_product_code(order.product_code) * order.quantity;

    // Create response YAML
    int len = asprintf(response_yaml, "total_price: %.2f", total_price);
    if (len < 0) {
        return -1;
    }

    free(order.product_code);
    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *response_yaml;
    double total_price = calculate_price(yaml_payload, &response_yaml);

    if (total_price >= 0) {
        printf("Response YAML:\n%s\n", response_yaml);
        free(response_yaml);
    } else {
        printf("Error processing request.\n");
    }

    return 0;
}