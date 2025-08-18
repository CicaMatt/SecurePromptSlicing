#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 25.50;
    if (strcmp(product_code, "C789") == 0) return 15.00;
    return -1.0; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto error;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            const char *value = (const char *)event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (strncmp(value, "product_code", 12) == 0 && value[12] == ':') {
                product_code = value + 13;
            } else if (strncmp(value, "quantity", 8) == 0 && value[8] == ':') {
                quantity = atoi(value + 9);
            }
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);

    yaml_parser_free(&parser);
    return strdup(buffer);

error:
    yaml_parser_free(&parser);
    return NULL;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    if (result) {
        printf("%s", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing YAML payload.\n");
    }
    return 0;
}