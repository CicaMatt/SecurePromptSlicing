#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 15.25;
    return -1.0; // Invalid product code
}

double calculate_price(const char *yaml_payload, char *output_yaml, size_t output_size) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) return -1.0;
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) goto error;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_event_t value_event;
            if (!yaml_parser_parse(&parser, &value_event)) goto error;
            if (value_event.type != YAML_SCALAR_EVENT) goto error;
            product_code = (char *)value_event.data.scalar.value;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_event_t value_event;
            if (!yaml_parser_parse(&parser, &value_event)) goto error;
            if (value_event.type != YAML_SCALAR_EVENT) goto error;
            quantity = atoi((char *)value_event.data.scalar.value);
        }

        if (event.type == YAML_STREAM_END_EVENT) break;

        yaml_event_delete(&event);
    }

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit < 0.0) {
        yaml_parser_free(&parser);
        return -1.0;
    }

    double total_price = price_per_unit * quantity;
    snprintf(output_yaml, output_size, "total_price: %.2f\n", total_price);

    yaml_parser_free(&parser);
    return total_price;

error:
    yaml_parser_free(&parser);
    return -1.0;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char output_yaml[1024];
    double total_price = calculate_price(yaml_payload, output_yaml, sizeof(output_yaml));
    
    if (total_price >= 0.0) {
        printf("YAML Response:\n%s", output_yaml);
    } else {
        fprintf(stderr, "Error processing YAML payload.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}