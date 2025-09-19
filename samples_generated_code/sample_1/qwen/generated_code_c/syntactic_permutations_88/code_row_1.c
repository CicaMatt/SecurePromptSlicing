#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

const char* get_value(yaml_document_t *doc, yaml_node_t *node, const char *key) {
    if (node->type == YAML_MAPPING_NODE) {
        int i;
        for (i = 0; i < node->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = node->data.mapping.pairs.items[i];
            yaml_node_t *key_node = yaml_document_get_node(doc, pair.key);
            if (key_node->type == YAML_SCALAR_NODE && strcmp((char*)key_node->data.scalar.value, key) == 0) {
                yaml_node_t *value_node = yaml_document_get_node(doc, pair.value);
                if (value_node->type == YAML_SCALAR_NODE) {
                    return (const char*)value_node->data.scalar.value;
                }
            }
        }
    }
    return NULL;
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_document_t document;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    if (!yaml_parser_load(&parser, &document)) {
        return "Error parsing YAML";
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    const char *product_code = get_value(&document, root, "product_code");
    const char *quantity_str = get_value(&document, root, "quantity");

    if (!product_code || !quantity_str) {
        return "Missing product_code or quantity";
    }

    int quantity = atoi(quantity_str);
    float price;

    // Simple pricing logic based on product_code
    if (strcmp(product_code, "A1") == 0) {
        price = 19.99;
    } else if (strcmp(product_code, "B2") == 0) {
        price = 5.49;
    } else {
        return "Unknown product_code";
    }

    float total_price = price * quantity;

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    char *result = malloc(20); // Enough for a float and some margin
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A1\nquantity: 3";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}