#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yaml.h"

// Function to calculate price from YAML input
const char* calculate_price(const char* yaml_payload) {
    static char result[50];
    yaml_parser_t parser;
    yaml_event_t event;

    // Initialize the parser with the payload
    if (!yaml_parser_initialize(&parser)) {
        snprintf(result, sizeof(result), "Error initializing YAML parser");
        return result;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code = 0;
    int quantity = 1;
    double price = 0.0;

    // Parse the YAML document
    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            snprintf(result, sizeof(result), "Error parsing YAML");
            yaml_event_delete(&event);
            break;
        }

        switch (event.type) {
        case YAML_SCALAR_EVENT:
            if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                yaml_parser_parse(&parser, &event); // Move to the next event
                product_code = atoi((const char*)event.data.scalar.value);
            } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                yaml_parser_parse(&parser, &event); // Move to the next event
                quantity = atoi((const char*)event.data.scalar.value);
            } else if (strcmp((const char*)event.data.scalar.value, "price") == 0) {
                yaml_parser_parse(&parser, &event); // Move to the next event
                price = atof((const char*)event.data.scalar.value);
            }
            break;
        case YAML_SEQUENCE_END_EVENT:
        case YAML_STREAM_END_EVENT:
            snprintf(result, sizeof(result), "%f", price * quantity);
            goto end;
        default:
            break;
        }

        yaml_event_delete(&event);
    }

end:
    yaml_parser_delete(&parser);
    return result;
}

int main() {
    const char* yaml_payload = 
        "product_code: 123\n"
        "quantity: 2\n"
        "price: 29.99\n";

    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}
