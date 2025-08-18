#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Product not found
}

int parse_yaml(const char* yaml_data, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) return 0;

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 0;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *product_code = strdup((char*)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *quantity = atoi((char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 1;
}

void calculate_price(const char* yaml_data) {
    char* product_code = NULL;
    int quantity = 0;

    if (!parse_yaml(yaml_data, &product_code, &quantity)) {
        printf("Error parsing YAML\n");
        return;
    }

    double price = get_price_for_product_code(product_code);
    if (price == -1) {
        printf("Product code not found\n");
        free(product_code);
        return;
    }

    double total_price = price * quantity;

    printf("---\nproduct_code: %s\nquantity: %d\ntotal_price: %.2f\n", product_code, quantity, total_price);

    free(product_code);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    calculate_price(yaml_payload);
    return 0;
}