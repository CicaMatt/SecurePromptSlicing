#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_BUFFER_SIZE 1024

const char* get_product_price(const char* product_code) {
    if (strcmp(product_code, "P001") == 0) return "19.99";
    else if (strcmp(product_code, "P002") == 0) return "5.49";
    else if (strcmp(product_code, "P003") == 0) return "15.75";
    return "0.00";
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    char product_code[64] = "";
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) return strdup("Error initializing parser");

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return strdup("Error parsing YAML");
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    strncpy(product_code, (const char*)event.data.scalar.value, sizeof(product_code));
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);

    const char* product_price_str = get_product_price(product_code);
    price = atof(product_price_str) * quantity;

    char* result = (char*)malloc(MAX_BUFFER_SIZE);
    snprintf(result, MAX_BUFFER_SIZE, "%.2f", price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: P001\nquantity: 3";
    char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}