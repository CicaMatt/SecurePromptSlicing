#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Product;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.50;
    if (strcmp(code, "B456") == 0) return 20.75;
    if (strcmp(code, "C789") == 0) return 5.25;
    return -1; // Product code not found
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    double total_price = 0;
    char product_code[10] = "";
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    strncpy(product_code, (char *)event.data.scalar.value, sizeof(product_code));
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char *)event.data.scalar.value);
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

    double price_per_unit = get_price_for_product_code(product_code);
    total_price = price_per_unit * quantity;

    char *response = malloc(256); // Allocate enough space for the YAML response
    snprintf(response, 256, "total_price: %.2f", total_price);
    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result); // Free allocated memory
    return 0;
}