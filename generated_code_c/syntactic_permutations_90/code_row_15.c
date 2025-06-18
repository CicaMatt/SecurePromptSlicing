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

### Explanation:

- First, include all necessary headers. In this case, stdio.h and string.h are the standard C headers for input/output and strings respectively. 
yaml.h is a header for YAML processing in C. It includes functions to parse and generate YAML data.
- Next, define the get_price_for_product_code() function that takes a product code as a string and returns the price of the corresponding product. The function uses strcmp() from string.h to compare the input product code with each possible product code and returns the respective price if there is a match.
- Then, define the calculate_price() function that takes a YAML payload as a string and returns the total price calculated from the payload. It first initializes a yaml_document_t structure for holding the parsed YAML data using yaml_parser_initialize(). This function sets up the parser state for parsing.
- Next, it sets the input string to be parsed by calling yaml_parser_set_input_string() with the payload and its length as arguments. If there is an error during this step, return 2.
- Then, load the YAML data into a document using yaml_parser_load(). This function reads the input stream and parses it as a YAML document. If there is an error during this step, return 3.
- Extract the root node of the YAML data using yaml_document_get_root_node(). The root node contains all the key-value pairs in the payload.
- Next, extract two nodes from the root node corresponding to the product code and quantity keys respectively by calling yaml_document_get_node() twice. Pass the index of the respective key-value pair as an argument.
- Extract the scalar values of the product code and quantity nodes using yaml_node_get_scalar_value(). The product code is a string value, and the quantity is an integer represented by a string in the YAML data. Use atoi() to convert the quantity string to an integer.
- Call get_price_for_product_code() with the extracted product code and multiply it by the quantity to calculate the total price.
- Format the result into a buffer using sprintf().
- Finally, delete the document to free up any memory allocated during parsing using yaml_document_delete(). Return the buffer containing the YAML data for the total price.