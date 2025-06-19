#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <yaml.h>

int get_price_for_product_code(char *product_code) {
    int price = 0;

    if (strcmp("A1", product_code) == 0) {
        price = 2399;
    } else if (strcmp("B2", product_code) == 0) {
        price = 3499;
    } else if (strcmp("C3", product_code) == 0) {
        price = 1599;
    } else if (strcmp("D4", product_code) == 0) {
        price = 1299;
    }

    return price;
}

void calculate_price(char *query_parameter) {
    char yaml_payload[50];
    sprintf(yaml_payload, "product_code: %s\nquantity: 3", query_parameter);

    yaml_document_t document;
    yaml_node_t *root_node = NULL;
    yaml_node_t *product_code = NULL;
    yaml_node_t *quantity = NULL;

    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, yaml_payload, strlen(yaml_payload));

    if (yaml_parser_load(&parser, &document)) {
        root_node = yaml_document_get_root_node(&document);
        product_code = yaml_document_get_node(&document, root_node->data.mapping.pairs.start[0].key);
        quantity = yaml_document_get_node(&document, root_node->data.mapping.pairs.start[1].value);
    }

    char *product_code_string = (char *)product_code->data.scalar.value;

    int price = get_price_for_product_code(product_code_string);
    int total_price = price * quantity->data.scalar.value;

    char result[50];
    sprintf(result, "total_price: %d", total_price);

    printf("%s\n", result);
}