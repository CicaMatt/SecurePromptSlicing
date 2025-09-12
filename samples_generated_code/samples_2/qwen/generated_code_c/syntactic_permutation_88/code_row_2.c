#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_PAYLOAD_SIZE 1024

const char* get_value(yaml_parser_t *parser, const char *key) {
    yaml_event_t event;
    int found = 0;
    const char *value = NULL;

    while (yaml_parser_parse(parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, key) == 0) {
            found = 1;
        } else if (event.type == YAML_SCALAR_EVENT && found) {
            value = (char *)event.data.scalar.value;
            break;
        }
        yaml_event_delete(&event);
    }

    return value;
}

const float get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99f;
    else if (strcmp(product_code, "B456") == 0) return 19.99f;
    else if (strcmp(product_code, "C789") == 0) return 29.99f;
    return 0.0f;
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    const char *product_code = get_value(&parser, "product_code");
    const char *quantity_str = get_value(&parser, "quantity");

    yaml_parser_delete(&parser);

    int quantity = atoi(quantity_str);
    float price = get_price(product_code);
    float total_price = price * quantity;

    static char result[32];
    snprintf(result, sizeof(result), "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 3";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}