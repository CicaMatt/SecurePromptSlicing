#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error: Failed to initialize parser";
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return "Error: Parsing failed";
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_event_t next;
            yaml_parser_parse(&parser, &next);
            product_code = (char *)next.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_event_t next;
            yaml_parser_parse(&parser, &next);
            quantity = atoi((char *)next.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_free(&parser);

    if (!product_code || quantity <= 0) {
        return "Error: Invalid input";
    }

    double price = 0.0;

    // Simple hardcoded pricing
    if (strcmp(product_code, "A") == 0) {
        price = 10.0;
    } else if (strcmp(product_code, "B") == 0) {
        price = 20.0;
    } else {
        return "Error: Unknown product code";
    }

    double total_price = price * quantity;

    char *result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);

    return result;
}

int main() {
    const char *payload = "product_code: A\nquantity: 3";
    char *price = calculate_price(payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}