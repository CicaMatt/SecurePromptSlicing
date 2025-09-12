#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char* query) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing parser";
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)query, strlen(query));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            return "Error parsing YAML";
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char*)event.data.scalar.value, "product_code") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) {
                return "Error parsing YAML";
            }
            product_code = (char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char*)event.data.scalar.value, "quantity") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) {
                return "Error parsing YAML";
            }
            quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_cleanup(&parser);

    if (!product_code || quantity <= 0) {
        return "Invalid product code or quantity";
    }

    double price = 0.0;

    // Example pricing logic
    if (strcmp(product_code, "A123") == 0) {
        price = 10.5;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 20.0;
    } else {
        return "Unknown product code";
    }

    double total_price = price * quantity;

    char* result = malloc(32);
    snprintf(result, 32, "%.2f", total_price);

    return result;
}

int main() {
    const char* query = "product_code: A123\nquantity: 5";
    char* price = calculate_price(query);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}