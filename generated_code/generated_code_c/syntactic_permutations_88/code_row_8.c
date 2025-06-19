#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "yaml.h"
    int main(void) {
        char *str = "product_code: BTC\nquantity: 20";
        yaml_parser_t parser;
        yaml_node_t node;
        int done = 0;
        yaml_token_t token;
        FILE* file = fopen("example.yaml", "w");
        fprintf(file, "%s", str);
        fclose(file);
        if (!yaml_parser_initialize(&parser)) {
            printf("Could not initialize parser!\n");
            return 1;
        }
        yaml_parser_set_input_string(&parser, (unsigned char*)str, strlen(str));
        while (!done) {
            if (!yaml_parser_scan(&parser, &token)) {
                printf("Could not scan the token!\n");
                return 1;
            }
            done = (token.type == YAML_STREAM_END_TOKEN);
        }
        yaml_parser_delete(&parser);
        if (!yaml_document_initialize(&document, &versionDirective, &tagDirectiveStart, &startImplicit, NULL, 1, 0)) {
            printf("Could not initialize document!\n");
            return 1;
        }
        if (!yaml_document_get_root_node(&document, &node)) {
            printf("Could not get root node!");
            yaml_parser_delete(&parser);
            return 1;
        }
        char *product_code = NULL;
        char *quantity = NULL;
        switch (node.type) {
          case YAML_MAPPING_NODE:
            break;
          default:
            printf("Expected mapping node, got %d\n", node.type);
            yaml_document_delete(&document);
            return 1;
        }
        for (int i = 0; i < node.data.mapping.pairs.length; i++) {
            yaml_node_pair_t *pair = &(node.data.mapping.pairs.start[i]);
            if (!strcmp((char*)pair->key.data.scalar.value, "product_code")) {
                product_code = (char*)pair->value.data.scalar.value;
            } else if (!strcmp((char*)pair->key.data.scalar.value, "quantity")) {
                quantity = (char*)pair->value.data.scalar.value;
            }
        }
        int price = 0;
        switch (product_code) {
          case "BTC":
            price = 10;
            break;
          case "ETH":
            price = 20;
            break;
          default:
            printf("Invalid product code!");
            yaml_document_delete(&document);
            return 1;
        }
        int total_price = price * atoi(quantity);
        char result[50];
        sprintf(result, "%d", total_price);
        return result;
    }