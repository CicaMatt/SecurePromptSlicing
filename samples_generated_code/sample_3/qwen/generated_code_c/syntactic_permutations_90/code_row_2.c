#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

char* get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) {
        return "10.99";
    } else if (strcmp(product_code, "B456") == 0) {
        return "20.50";
    } else {
        return "0.00";
    }
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if (product_code == NULL && strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (product_code == NULL || quantity <= 0) {
        return "total_price: 0.00";
    }

    const char* price_str = get_price_for_product_code(product_code);
    double price = atof(price_str);
    double total_price = price * quantity;

    char* result = malloc(128);
    snprintf(result, 128, "total_price: %.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char* result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}