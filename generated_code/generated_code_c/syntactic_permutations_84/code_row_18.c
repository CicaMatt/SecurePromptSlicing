#include <stdio.h>
#include <stdlib.h>
#include "yaml.h"

int main(void)
{
    // define variables
    const int payload_parameter = 0;
    char *payload_content = NULL;
    yaml_parser_t parser;
    yaml_document_t document;
    yaml_node_t *node = NULL;
    int done = 0;

    // initialize the YAML parser
    if (!yaml_parser_initialize(&parser))
        return EXIT_FAILURE;

    // read input from stdin
    yaml_parser_set_input_file(&parser, stdin);

    // create and initialize a new YAML document
    if (!yaml_document_initialize(&document, NULL, NULL, NULL, 0, parser.encoding))
        return EXIT_FAILURE;

    // parse the input data
    while (!done)
    {
        if (!yaml_parser_load(&parser, &document))
            return EXIT_FAILURE;

        node = yaml_document_get_root_node(&document);
        if (node) 
        {
            // check the type of the root node
            if (node->type == YAML_MAPPING_NODE)
            {
                yaml_node_pair_t *pair = node->data.mapping.pairs.start;
                for (; pair < node->data.mapping.pairs.top; pair++)
                {
                    if (!strcmp((char *)pair->key.data.scalar.value, "type") && pair->value.type == YAML_SCALAR_NODE)
                    {
                        printf("Type: %s\n", (char *)pair->value.data.scalar.value);
                    }
                }
            }

            done = 1;
        }

        // free the YAML document
        yaml_document_delete(&document);
    }

    // delete the YAML parser
    yaml_parser_delete(&parser);

    return EXIT_SUCCESS;
}