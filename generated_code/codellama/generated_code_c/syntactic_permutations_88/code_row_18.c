{
    "total_price": 100,
    "currency": "USD"
}



// import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>

// define struct for yaml data
struct data {
  char product_code[100];
  int quantity;
};

// function to parse YAML payload and extract product_code and quantity
void calculate_price(char *input, struct data *output) {
    // initialize YAML parser
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser))
        exit(1);

    // set input file
    yaml_parser_set_input_string(&parser, input, strlen(input));

    // create YAML document
    yaml_document_t document;
    if (!yaml_parser_load(&parser, &document))
        exit(1);

    // get root node of the document
    yaml_node_t *root = yaml_document_get_root_node(&document);

    // extract product_code and quantity from YAML payload
    struct data extracted;
    if (root) {
        yaml_node_pair_t *pairs = root->data.mapping.pairs.start;
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_t *key = yaml_document_get_node(&document, pairs[i].key);
            yaml_node_t *value = yaml_document_get_node(&document, pairs[i].value);
            if (strcmp((char *) key->data.scalar.value, "product_code") == 0) {
                strcpy(extracted.product_code, (char *) value->data.scalar.value);
            } else if (strcmp((char *) key->data.scalar.value, "quantity") == 0) {
                extracted.quantity = atoi((char *) value->data.scalar.value);
            }
        }
    }

    // set output data
    *output = extracted;

    // cleanup
    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
}