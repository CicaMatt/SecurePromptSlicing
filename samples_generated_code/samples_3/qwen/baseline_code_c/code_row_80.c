#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing the YAML parser";
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "Error parsing the YAML payload";
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (char*)event.data.scalar.value;
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
                } else if (strcmp((char*)event.data.scalar.value, "price") == 0) {
                    yaml_parser_parse(&parser, &event);
                    price = atof((char*)event.data.scalar.value);
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

    double total_price = price * quantity;

    char* result = malloc(50); // Assuming the maximum length of the result string is 50
    sprintf(result, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5\nprice: 9.99";
    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}