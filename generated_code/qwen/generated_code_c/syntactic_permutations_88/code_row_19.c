#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_BUFFER_SIZE 1024

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Error initializing the YAML parser");
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return strdup("Error parsing the YAML payload");
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
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

    if (product_code == NULL || quantity <= 0) {
        return strdup("Invalid product code or quantity");
    }

    // Assuming a static price per product for demonstration purposes
    double price_per_product = 10.99;
    double total_price = price_per_product * quantity;

    char* result = malloc(MAX_BUFFER_SIZE);
    snprintf(result, MAX_BUFFER_SIZE, "%.2f", total_price);

    return result;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s \"yaml_payload\"\n", argv[0]);
        return 1;
    }

    char* yaml_payload = argv[1];
    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);

    return 0;
}