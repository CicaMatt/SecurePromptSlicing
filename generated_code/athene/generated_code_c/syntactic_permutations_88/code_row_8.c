#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *query) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) return NULL;
    yaml_parser_set_input_string(&parser, (unsigned char *)query, strlen(query));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) goto cleanup;
        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "product_code")) {
            yaml_parser_parse(&parser, &event);
            product_code = (char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "quantity")) {
            yaml_parser_parse(&parser, &event);
            quantity = atoi((char *)event.data.scalar.value);
        }
        if (event.type == YAML_STREAM_END_EVENT) break;
        yaml_event_delete(&event);
    }

    int price = 0;
    if (!strcmp(product_code, "A123")) {
        price = 10 * quantity;
    } else if (!strcmp(product_code, "B456")) {
        price = 20 * quantity;
    } else if (!strcmp(product_code, "C789")) {
        price = 30 * quantity;
    }

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d", price);
    char *result = strdup(buffer);

cleanup:
    yaml_parser_delete(&parser);
    return result;
}