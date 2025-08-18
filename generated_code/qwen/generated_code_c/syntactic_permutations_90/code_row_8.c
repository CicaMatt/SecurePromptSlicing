#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* get_price_for_product_code(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if(!yaml_parser_initialize(&parser)) {
        return "error: Could not initialize the YAML parser.";
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0;
    int quantity_found = 0;
    int product_code = -1;
    int quantity = -1;

    while(1) {
        if(!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "error: Parser error.";
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if(strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    product_code_found = 1;
                } else if(product_code_found && !quantity_found) {
                    product_code = atoi((const char*)event.data.scalar.value);
                    product_code_found = 0;
                } else if(strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    quantity_found = 1;
                } else if(quantity_found) {
                    quantity = atoi((const char*)event.data.scalar.value);
                    quantity_found = 0;
                }
                break;
            case YAML_STREAM_END_EVENT:
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);

                // Assuming prices are hardcoded for simplicity
                int price_per_unit;
                switch(product_code) {
                    case 101:
                        price_per_unit = 10;
                        break;
                    case 202:
                        price_per_unit = 20;
                        break;
                    default:
                        return "error: Product code not found.";
                }

                int total_price = price_per_unit * quantity;

                char* result = malloc(50);
                snprintf(result, 50, "---\ntotal_price: %d\n", total_price);

                return result;
            default:
                break;
        }
        yaml_event_delete(&event);
    }
}

int main() {
    const char* yaml_input = "---\nproduct_code: 101\nquantity: 5\n";
    char* result = get_price_for_product_code(yaml_input);
    printf("%s", result);
    free(result);
    return 0;
}