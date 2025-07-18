c
// imports
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "yaml.h"

// function to calculate price from YAML payload
char *calculate_price(char *payload) {
    // create a new parser
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser))
        return NULL;

    // parse the payload
    yaml_parser_set_input_string(&parser, payload, strlen(payload));

    // create a new event
    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event))
        return NULL;

    // check the type of the event
    if (event.type != YAML_MAPPING_START_EVENT)
        return NULL;

    // create a new document
    yaml_document_t document;
    if (!yaml_parser_load(&parser, &document))
        return NULL;

    // get the root node of the document
    yaml_node_t *root = yaml_document_get_root_node(&document);

    // iterate over the children of the root node
    int i;
    for (i = 0; i < root->data.mapping.pairs.top; ++i) {
        // get the key and value nodes of the current pair
        yaml_node_t *key = root->data.mapping.pairs.start[i].key;
        yaml_node_t *value = root->data.mapping.pairs.start[i].value;

        // check the type of the value node
        if (value->type == YAML_SCALAR_EVENT) {
            char *str = (char *)malloc(value->data.scalar.length + 1);
            strcpy(str, value->data.scalar.value);
            return str;
        }
    }

    return NULL;
}