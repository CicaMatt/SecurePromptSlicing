#include <stdio.h>
    int get_price_for_product_code(char *code) {
        if (strcmp(code, "ABC") == 0) return 12;
        if (strcmp(code, "XYZ") == 0) return 24;
        return -1;
    }

    #include <yaml.h>
    int calculate_price(char *payload) {
        yaml_document_t document;
        yaml_parser_t parser;
        yaml_node_t *root_node = NULL;
        yaml_node_t *product_code_node = NULL;
        yaml_node_t *quantity_node = NULL;

        int result;
        int product_code;
        int quantity;
        int total_price;

        char *error_message = NULL;

        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, payload, strlen(payload));

        result = yaml_parser_load(&parser, &document);
        if (result == 0) {
            error_message = "YAML parsing failed";
            goto cleanup;
        }

        root_node = yaml_document_get_root_node(&document);
        product_code_node = yaml_document_get_node(&document, root_node->data.mapping.pairs.start[0].key);
        quantity_node = yaml_document_get_node(&document, root_node->data.mapping.pairs.start[1].key);

        product_code = atoi(product_code_node->data.scalar.value);
        quantity = atoi(quantity_node->data.scalar.value);

        total_price = get_price_for_product_code(product_code) * quantity;

        yaml_document_delete(&document);
    }