#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>

double get_product_price(const char *product_code) {
    // Placeholder function to return a fixed price for demonstration purposes.
    if (strcmp(product_code, "A") == 0) {
        return 10.0;
    } else if (strcmp(product_code, "B") == 0) {
        return 20.0;
    }
    return 0.0; // Default price for unknown product codes
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    // Initialize the parser
    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser!\n");
        return -1.0;
    }

    // Set input source for the parser
    if (!yaml_parser_set_input_string(&parser, yaml_payload, strlen(yaml_payload))) {
        fprintf(stderr, "Failed to set YAML input string!\n");
        yaml_parser_delete(&parser);
        return -1.0;
    }

    const char *product_code = NULL;
    int quantity = 0;

    // Parse the YAML document
    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Failed to parse YAML event!\n");
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1.0;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "product_code") == 0) {
                    // Get the next scalar event which should be product code
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char *)event.data.scalar.value;
                } else if (strcmp((const char *)event.data.scalar.value, "quantity") == 0) {
                    // Get the next scalar event which should be quantity
                    yaml_parser_parse(&parser, &event);
                    sscanf((const char *)event.data.scalar.value, "%d", &quantity);
                }
                break;

            case YAML_STREAM_END_EVENT:
                goto end;
        }

        yaml_event_delete(&event);
    }

end:
    // Clean up the parser and event
    yaml_event_delete(&event);
    yaml_parser_delete(&parser);

    if (product_code == NULL || quantity <= 0) {
        fprintf(stderr, "Invalid input: product code or quantity not provided\n");
        return -1.0;
    }

    double price_per_unit = get_product_price(product_code);
    return price_per_unit * quantity;
}

int main() {
    const char *yaml_payload =
        "---\n"
        "product_code: A\n"
        "quantity: 3\n";

    double total_price = calculate_price(yaml_payload);

    if (total_price >= 0) {
        printf("Total Price: %.2f\n", total_price);
    } else {
        fprintf(stderr, "Error calculating price.\n");
    }

    return 0;
}