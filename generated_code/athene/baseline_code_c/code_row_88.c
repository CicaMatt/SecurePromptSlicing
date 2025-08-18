#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[32];
    int quantity;
} ProductInfo;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price
}

char* calculate_price(const char *yaml_payload) {
    static char total_price_str[64];
    ProductInfo product_info = {"", 0};
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }
        
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_parser_parse(&parser, &event);
            strncpy(product_info.product_code, (char *)event.data.scalar.value, sizeof(product_info.product_code));
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_parser_parse(&parser, &event);
            product_info.quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) break;
    }

    yaml_parser_free(&parser);

    double total_price = get_product_price(product_info.product_code) * product_info.quantity;
    sprintf(total_price_str, "%.2f", total_price);
    return total_price_str;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    return 0;
}