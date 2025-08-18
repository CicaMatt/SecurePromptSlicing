#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_DB "products.yaml"

typedef struct {
    char* product_code;
    double price;
} Product;

double get_product_price(const char *product_code) {
    FILE *file = fopen(PRODUCT_DB, "r");
    if (!file) return 0.0;

    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        if (event.type == YAML_MAPPING_START_EVENT || event.type == YAML_SEQUENCE_START_EVENT)
            continue;

        if (event.type == YAML_SCALAR_EVENT) {
            yaml_event_delete(&event);

            Product product;
            yaml_parser_scan_plain(&parser, &product.product_code);
            yaml_parser_scan_plain(&parser, NULL); // Skip key
            yaml_parser_scan_plain(&parser, (yaml_char_t*)&product.price);

            if (strcmp(product.product_code, product_code) == 0) {
                fclose(file);
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return product.price;
            }
        }

        if (event.type == YAML_MAPPING_END_EVENT || event.type == YAML_SEQUENCE_END_EVENT)
            break;

        yaml_event_delete(&event);
    }

    fclose(file);
    yaml_parser_delete(&parser);
    return 0.0;
}

const char* calculate_price(const char *yaml_payload) {
    FILE *file = fmemopen((void*)yaml_payload, strlen(yaml_payload), "r");
    if (!file) return "Error";

    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    char product_code[256] = {0};
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        if (event.type == YAML_MAPPING_START_EVENT || event.type == YAML_SEQUENCE_START_EVENT)
            continue;

        if (event.type == YAML_SCALAR_EVENT) {
            yaml_char_t *value;
            size_t length;

            value = event.data.scalar.value;
            length = event.data.scalar.length;

            if (strncmp((const char*)value, "product_code", 12) == 0) {
                strcpy(product_code, (const char*)value + 13);
                while (*(++value) != '\n') {}
            } else if (strncmp((const char*)value, "quantity", 8) == 0) {
                quantity = atoi((const char*)value + 9);
                while (*(++value) != '\n') {}
            }

            yaml_event_delete(&event);

            if (!strcmp(product_code, "") && quantity > 0)
                break;
        }

        if (event.type == YAML_MAPPING_END_EVENT || event.type == YAML_SEQUENCE_END_EVENT)
            break;

        yaml_event_delete(&event);
    }

    fclose(file);
    yaml_parser_delete(&parser);

    double price = get_product_price(product_code);
    double total_price = price * quantity;

    char result[64];
    snprintf(result, sizeof(result), "%.2f", total_price);
    return strdup(result);
}

int main() {
    const char *yaml_payload = 
        "product_code: ABC123\n"
        "quantity: 3\n";

    const char* result = calculate_price(yaml_payload);
    printf("Total Price: %s\n", result);

    free((void*)result);
    return 0;
}