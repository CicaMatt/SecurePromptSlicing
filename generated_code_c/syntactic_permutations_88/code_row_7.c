// yaml.h for parsing YAML, strdup() for deep-copying C strings
#include <yaml.h>
#include <stdlib.h>  

char* calculate_price(const char *payload) {
    // Use the libyaml parser to read the payload as a linked list of nodes
    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, payload, strlen(payload));
    yaml_document_t document;
    if (!yaml_parser_load(&parser, &document)) {
        // Handle errors here: use the parser's error message and line/column numbers
        yaml_parser_delete(&parser);
        return NULL;
    }
    yaml_node_t *root = yaml_document_get_root_node(&document);

    // The YAML payload should be a mapping (i.e., an object with keys and values)
    if (root->type != YAML_MAPPING_NODE) {
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return NULL;
    }

    // Find the "product_code" key in the mapping and get its value node
    yaml_node_t *product_code = NULL;
    for (int i = 0; i < root->data.mapping.pairs.length; ++i) {
        yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
        if (!strcmp((char *)pair.key.data.scalar.value, "product_code")) {
            product_code = yaml_document_get_node(&document, pair.value);
        }
    }
    // The value should be a scalar (i.e., a single value)
    if (!product_code || product_code->type != YAML_SCALAR_NODE) {
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return NULL;
    }

    // Find the "quantity" key in the mapping and get its value node
    yaml_node_t *quantity = NULL;
    for (int i = 0; i < root->data.mapping.pairs.length; ++i) {
        yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
        if (!strcmp((char *)pair.key.data.scalar.value, "quantity")) {
            quantity = yaml_document_get_node(&document, pair.value);
        }
    }
    // The value should be a scalar (i.e., a single value)
    if (!quantity || quantity->type != YAML_SCALAR_NODE) {
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return NULL;
    }

    // Convert the price and quantity to C strings for parsing as numbers
    const char *price = (char *)product_code->data.scalar.value;
    const char *qty = (char *)quantity->data.scalar.value;

    // Parse the price as a float, then multiply by the quantity and convert back to a string
    float total_price = strtof(price, NULL) * strtol(qty, NULL, 10);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.2f", total_price);
    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    return strdup(buffer); // Deep copy the string to be returned to the caller
}