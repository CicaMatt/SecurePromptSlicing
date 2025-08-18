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

int parse_yaml(const char *yaml_str, char **product_code, int *quantity) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *key = NULL;
    double value = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_str, strlen(yaml_str));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) goto error;
        if (event.type == YAML_SCALAR_EVENT && key == NULL) {
            key = (const char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && key != NULL) {
            value = atof((const char *)event.data.scalar.value);
            if (strcmp(key, "product_code") == 0) {
                *product_code = strdup((const char *)event.data.scalar.value);
            } else if (strcmp(key, "quantity") == 0) {
                *quantity = (int)value;
            }
            key = NULL;
        } else if (event.type == YAML_STREAM_END_EVENT) break;

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0;

error:
    yaml_parser_delete(&parser);
    return -1;
}

void calculate_price(const char *yaml_payload, char *output, size_t output_size) {
    char *product_code = NULL;
    int quantity = 0;
    double price = 0.0;
    double total_price = 0.0;

    if (parse_yaml(yaml_payload, &product_code, &quantity) == -1) {
        snprintf(output, output_size, "error: invalid YAML payload");
        return;
    }

    price = get_price_for_product_code(product_code);
    if (price < 0) {
        snprintf(output, output_size, "error: invalid product code");
        free(product_code);
        return;
    }

    total_price = price * quantity;

    snprintf(output, output_size, "total_price: %.2f", total_price);

    free(product_code);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char output[1024];

    calculate_price(yaml_payload, output, sizeof(output));

    printf("%s\n", output);

    return 0;
}