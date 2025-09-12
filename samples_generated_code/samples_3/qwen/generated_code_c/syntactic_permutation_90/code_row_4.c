#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 4.99;
    return -1.0; // Unknown product code
}

void parse_yaml(const char* yaml_data, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *product_code = strdup((char*)event.data.scalar.value);
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
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
}

void calculate_price(const char* yaml_data) {
    char* product_code = NULL;
    int quantity = 0;

    parse_yaml(yaml_data, &product_code, &quantity);

    if (product_code == NULL || quantity <= 0) {
        printf("Invalid input\n");
        return;
    }

    double price = get_price_for_product_code(product_code);
    if (price < 0.0) {
        printf("Product not found\n");
        free(product_code);
        return;
    }

    double total_price = price * quantity;

    printf("total_price: %.2f\n", total_price);

    free(product_code);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    calculate_price(argv[1]);

    return EXIT_SUCCESS;
}