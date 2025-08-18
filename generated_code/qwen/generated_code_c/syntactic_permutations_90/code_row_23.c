#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.99;
    if (strcmp(product_code, "B") == 0) return 5.49;
    if (strcmp(product_code, "C") == 0) return 3.99;
    return 0.0;
}

int calculate_price(const char *yaml_payload, char **result_yaml) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        return EXIT_FAILURE;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return EXIT_FAILURE;
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                const char *product_code = (const char *)event.data.scalar.value;
                double price = get_price_for_product_code(product_code);
                total_price += price;
                break;
            }
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    *result_yaml = malloc(64); // Allocate enough space for the result
    sprintf(*result_yaml, "total_price: %.2f\n", total_price);

    return EXIT_SUCCESS;
}

int main() {
    const char *yaml_payload = "A\nB\nC";
    char *result_yaml;

    if (calculate_price(yaml_payload, &result_yaml) == EXIT_SUCCESS) {
        printf("%s", result_yaml);
        free(result_yaml);
    }

    return 0;
}