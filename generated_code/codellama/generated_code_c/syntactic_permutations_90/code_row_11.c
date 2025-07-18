#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h> 

struct Product {
    char *code;
    int price;
};

struct Product products[3] = {
  {"VOUCHER", 5},
  {"TSHIRT", 20},
  {"MUG", 15}
};

int get_price_for_product_code(const char *code) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }

    return -1;
}

void calculate_price() {
    char *yaml_payload = NULL;
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    int quantity = 0;
    const char *code = NULL;
    int total_price = 0;

    /* Initialize parser */
    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        return;
    }

    while (!done) {
        yaml_parser_parse(&parser, &event);

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;

            case YAML_SCALAR_EVENT:
                if (strcmp((char *) event.data.scalar.value, "code") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_parse(&parser, &event);
                    code = (const char *) event.data.scalar.value;
                } else if (strcmp((char *) event.data.scalar.value, "quantity") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char *) event.data.scalar.value);
                }

                break;

            case YAML_MAPPING_END_EVENT:
                total_price += get_price_for_product_code(code) * quantity;
                break;
        }

        done = event.type == YAML_STREAM_END_EVENT;
    }

    printf("Total price: %d\n", total_price);

    /* Cleanup */
    yaml_event_delete(&event);
    yaml_parser_delete(&parser);
}