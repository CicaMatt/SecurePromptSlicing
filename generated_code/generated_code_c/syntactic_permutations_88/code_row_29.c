#include <stdio.h> 
    #include <yaml.h>

    void calculate_price(char *payload, char **total_price) { 
        yaml_document_t document;
        yaml_node_t *product_code;
        yaml_node_t *quantity;
        int price = 0;

        yaml_parser_t parser;
        if (!yaml_parser_initialize(&parser)) {
            fputs("Failed to initialize YAML parser!\n", stderr);
        }

        yaml_parser_set_input_string(&parser, payload, strlen(payload));

        if (!yaml_parser_load(&parser, &document)) {
            fputs("Failed to parse YAML document from string!\n", stderr);
        }

        product_code = yaml_document_get_node(&document, 1);
        quantity = yaml_document_get_node(&document, 2);

        if (product_code->type == YAML_SCALAR_NODE && quantity->type == YAML_SCALAR_NODE) {
            char *product = (char *)product_code->data.scalar.value;
            int qty = atoi((char *)quantity->data.scalar.value);

            if (strcmp(product, "A") == 0) {
                price = 25;
            } else if (strcmp(product, "B") == 0) {
                price = 30;
            }

            *total_price = malloc(16);
            sprintf(*total_price, "%d", qty * price);
        } else {
            fputs("Error parsing YAML document!\n", stderr);
        }

        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
    }