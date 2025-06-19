#include <string.h>
    #include <stdlib.h>
    #include <yaml.h>
    
    double calculate_price(const char *product_code, int quantity) {
        if (strcmp(product_code, "VOUCHER") == 0) {
            return 5.0 * quantity;
        }
        else if (strcmp(product_code, "TSHIRT") == 0) {
            return 20.0 * quantity;
        }
        else if (strcmp(product_code, "MUG") == 0) {
            return 7.5 * quantity;
        }
        
        return -1;
    }
    
    int main() {
        yaml_parser_t parser;
        yaml_event_t event;
        
        char *payload = "---\nproduct_code: VOUCHER\nquantity: 5";
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, (const unsigned char *) payload, strlen(payload));
        
        if (!yaml_parser_parse(&parser, &event)) {
            printf("Failed to parse YAML string!");
            return 1;
        }
        
        yaml_document_t document;
        if (!yaml_parser_load(&parser, &document)) {
            printf("Failed to load the YAML document from parser!");
            return 1;
        }
        
        yaml_node_t *root = yaml_document_get_root_node(&document);
        if (!yaml_node_is_mapping(root)) {
            printf("The root node is not a mapping node!");
            return 1;
        }
        
        int quantity = -1;
        char *product_code = NULL;
        yaml_node_pair_t *pair = root->data.mapping.pairs.start;
        for (int i = 0; i < root->data.mapping.pairs.top; ++i, ++pair) {
            if (strcmp((const char *) pair->key.data.scalar.value, "quantity") == 0) {
                quantity = atoi((const char *) pair->value.data.scalar.value);
            }
            else if (strcmp((const char *) pair->key.data.scalar.value, "product_code") == 0) {
                product_code = (char *) pair->value.data.scalar.value;
            }
        }
        
        double price = calculate_price(product_code, quantity);
        if (price < 0) {
            printf("Invalid product code!");
            return 1;
        }
        else {
            printf("%s\n", "---\ntotal_price: X.XX");
        }
        
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        
        return 0;
    }