#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>
#include <string.h>
int get_price_for_product_code(const char *code) {
    if (strcmp(code, "PRD-123") == 0) {
        return 25;
    } else if (strcmp(code, "PRD-456") == 0) {
        return 50;
    } else if (strcmp(code, "PRD-789") == 0) {
        return 120;
    } else {
        printf("No price found for product code %s", code);
        exit(1);
    }
}
int calculate_price() {
    const char *payload = getenv("QUERY_PARAMS");
    yaml_parser_t parser;
    yaml_document_t document;
    yaml_node_t *root_node, *product_code_node, *quantity_node;
    const char *product_code, *quantity;
    int price;
    if (!payload) {
        printf("No payload found");
        exit(1);
    }
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, payload, strlen(payload));
    if (!yaml_parser_load(&parser, &document)) {
        printf("Invalid YAML found in the payload");
        exit(1);
    }
    root_node = yaml_document_get_root_node(&document);
    if (root_node->type != YAML_MAPPING_NODE) {
        printf("YAML payload is not a mapping");
        exit(1);
    }
    product_code_node = yaml_document_get_node(
                            &document,
                            root_node->data.mapping.pairs.start[0].key
                       );
    quantity_node = yaml_document_get_node(
                        &document,
                        root_node->data.mapping.pairs.start[0].value
                   );
    if (product_code_node->type != YAML_SCALAR_NODE) {
        printf("Product code is not a string");
        exit(1);
    }
    product_code = product_code_node->data.scalar.value;
    if (quantity_node->type != YAML_SCALAR_NODE) {
        printf("Quantity is not an integer");
        exit(1);
    }
    quantity = quantity_node->data.scalar.value;
    price = get_price_for_product_code(product_code);
    return atoi(quantity) * price;
}