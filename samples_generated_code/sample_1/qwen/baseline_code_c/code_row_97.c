#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_BUFFER_SIZE 1024

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    char product_code[64] = "";
    int quantity = 0;
    float price = 0.0f;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "Error parsing YAML";
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    strncpy(product_code, (const char*)event.data.scalar.value, sizeof(product_code) - 1);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "price") == 0) {
                    yaml_parser_parse(&parser, &event);
                    price = atof((const char*)event.data.scalar.value);
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

    if (strcmp(product_code, "") == 0 || quantity <= 0 || price <= 0.0f) {
        return "Invalid YAML payload";
    }

    float total_price = price * quantity;
    char* result = malloc(MAX_BUFFER_SIZE);
    snprintf(result, MAX_BUFFER_SIZE, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5\nprice: 9.99";
    char* price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price_str);
    free(price_str);
    return 0;
}