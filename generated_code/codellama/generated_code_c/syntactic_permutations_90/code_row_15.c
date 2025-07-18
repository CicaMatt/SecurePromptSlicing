#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <yaml.h>
    
    
    int get_price_for_product_code(const char* product_code) {
      if (strcmp(product_code, "A1") == 0) return 25;
      else if (strcmp(product_code, "B2") == 0) return 36;
      else if (strcmp(product_code, "C3") == 0) return 48;
      else return -1;
    }
    
    int calculate_price(const char* payload) {
      yaml_document_t document;
      yaml_node_t* root_node = NULL;
    
      yaml_parser_t parser;
      if (!yaml_parser_initialize(&parser)) {
        return 1;
      }
      if (yaml_parser_set_input_string(&parser, payload, strlen(payload))) {
        return 2;
      }
    
      if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        return 3;
      }
      root_node = yaml_document_get_root_node(&document);
    
      yaml_node_t* product_code_node = yaml_document_get_node(
          &document, root_node->data.mapping.pairs.start[0].key);
      yaml_node_t* quantity_node = yaml_document_get_node(
          &document, root_node->data.mapping.pairs.start[1].key);
    
      const char* product_code = yaml_node_get_scalar_value(product_code_node);
      int quantity = atoi(yaml_node_get_scalar_value(quantity_node));
      int price = get_price_for_product_code(product_code) * quantity;
    
      char buffer[128];
      sprintf(buffer, "total: %d", price);
      yaml_document_delete(&document);
      return buffer;
    }
