#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <yaml.h>

    float get_price_for_product_code(char *product_code){
        if (strcmp(product_code, "036") == 0) {
            return 49.95;
        } else if (strcmp(product_code, "187") == 0) {
            return 29.95;
        } else {
            return -1;
        }
    }

    int calculate_price(char *query){
        yaml_parser_t parser;
        yaml_token_t token;
        if (!yaml_parser_initialize(&parser)){
            fprintf(stderr, "Failed to initialize parser!\n");
        }
        yaml_parser_set_input_string(&parser, query, strlen(query));
        
        int done = 0;
        char *product_code;
        float quantity;
        while (!done){
            if (!yaml_parser_scan(&parser, &token)){
                fprintf(stderr, "Failed to scan token!\n");
                break;
            }
            switch(token.type){
                case YAML_SCALAR_TOKEN:
                    char *value = token.data.scalar.value;
                    if (strcmp(value, "product_code") == 0) {
                        product_code = yaml_parser_scan(&parser, &token).data.scalar.value;
                    } else if (strcmp(value, "quantity") == 0) {
                        quantity = atoi(yaml_parser_scan(&parser, &token).data.scalar.value);
                    }
                    break;
                case YAML_STREAM_END_TOKEN:
                    done = 1;
            }
        }
        
        float total_price = get_price_for_product_code(product_code) * quantity;
        printf("total price: %f", total_price);
        yaml_token_delete(&token);
        return 0;
    }