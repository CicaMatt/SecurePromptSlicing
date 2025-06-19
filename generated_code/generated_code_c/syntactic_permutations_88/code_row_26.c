#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "yaml.h"
    
    int calculate_price(char* payload){
        yaml_parser_t parser;
        yaml_node_t *root, *product_code, *quantity;
        double total_price = 0.0;
        char *product_code_value = NULL;
        int quantity_value = -1;
    
        if (yaml_parser_initialize(&parser)){
            yaml_parser_set_input_string(&parser, payload, strlen(payload));
            if (yaml_parser_load(&parser, &root)){
                product_code = yaml_document_get_node(&root->document, 1);
                quantity = yaml_document_get_node(&root->document, 2);
    
                product_code_value = (char*)product_code->data.scalar.value;
                quantity_value = atoi(quantity->data.scalar.value);
            }
        }
        yaml_parser_delete(&parser);
    
        if (product_code_value && (quantity_value >= 0)){
            total_price = calculate_price_from_db(product_code_value) * quantity_value;
        }
    
        return total_price;
    }