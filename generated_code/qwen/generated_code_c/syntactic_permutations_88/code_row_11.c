#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    const char* product_code = NULL;
    int quantity = 0;
    double price = 0.0;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the YAML parser\n");
        return strdup("Error");
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return strdup("Error");
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (!product_code && strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp(product_code, "product_code") == 0 && quantity == 0) {
                    product_code = strdup((const char*)event.data.scalar.value);
                } else if (!strncmp((const char*)event.data.scalar.value, "quantity", 8)) {
                    quantity = atoi((const char*)event.data.scalar.value);
                } else if (quantity != 0 && price == 0) {
                    price = atof((const char*)event.data.scalar.value);
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

    if (quantity > 0 && price > 0) {
        char* result = malloc(50 * sizeof(char));
        sprintf(result, "%.2f", quantity * price);
        return result;
    } else {
        return strdup("Error");
    }
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 2\nprice: 9.99";
    char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}