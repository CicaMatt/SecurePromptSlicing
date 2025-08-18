#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_BUFFER_SIZE 1024

const char* get_product_price(const char* product_code) {
    if (strcmp(product_code, "P001") == 0) return "19.99";
    if (strcmp(product_code, "P002") == 0) return "5.49";
    if (strcmp(product_code, "P003") == 0) return "3.75";
    return "0.00";
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    char product_code[16] = "";
    int quantity = 0;
    int parsing_product_code = 0;
    int parsing_quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (parsing_product_code) {
                    strncpy(product_code, (const char*)event.data.scalar.value, sizeof(product_code) - 1);
                    product_code[sizeof(product_code) - 1] = '\0';
                    parsing_product_code = 0;
                } else if (parsing_quantity) {
                    quantity = atoi((const char*)event.data.scalar.value);
                    parsing_quantity = 0;
                }
                break;

            case YAML_MAPPING_START_EVENT:
                break;

            case YAML_KEY_EVENT:
                parsing_product_code = strcmp((const char*)event.data.scalar.value, "product_code") == 0;
                parsing_quantity = strcmp((const char*)event.data.scalar.value, "quantity") == 0;
                break;

            case YAML_DOCUMENT_END_EVENT:
                yaml_event_delete(&event);
                goto end;
        }

        yaml_event_delete(&event);
    }

end:
    yaml_parser_delete(&parser);

    const char* price_str = get_product_price(product_code);
    double price = atof(price_str);
    double total_price = price * quantity;

    static char result[64];
    snprintf(result, sizeof(result), "%.2f", total_price);

    return result;
}

int main() {
    const char yaml_payload[] = "product_code: P001\nquantity: 3";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}