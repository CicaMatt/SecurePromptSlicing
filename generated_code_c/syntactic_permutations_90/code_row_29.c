#include <stdlib.h>
#include <string.h>
#include "yaml.h"

float get_price_for_product_code(const char *product_code)
{
    if (strcmp(product_code, "VOUCHER") == 0)
    {
        return 2.99;
    }
    else if (strcmp(product_code, "TSHIRT") == 0)
    {
        return 19.99;
    }
    else if (strcmp(product_code, "CAP") == 0)
    {
        return 4.95;
    }
}

#define YAML_BUFFER_SIZE 256
char *calculate_price(const char *yaml_payload)
{
    yaml_document_t document;
    if (yaml_document_initialize(&document, NULL, NULL, NULL, 0, 0) == 0)
    {
        printf("Failed to initialize document");
        return NULL;
    }
    if (yaml_parser_load(&document, yaml_payload, strlen(yaml_payload)) == 0)
    {
        printf("Failed to parse payload");
        return NULL;
    }
    const yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root->type != YAML_MAPPING_NODE || root->data.mapping.pairs.start == NULL)
    {
        printf("Invalid payload format");
        return NULL;
    }
    const yaml_node_pair_t *pairs = root->data.mapping.pairs.start;
    const yaml_node_t *product_code_node = pairs[0].key;
    if (product_code_node->type != YAML_SCALAR_NODE || product_code_node->data.scalar.length == 0)
    {
        printf("Invalid product code");
        return NULL;
    }
    const yaml_node_t *quantity_node = pairs[1].key;
    if (quantity_node->type != YAML_SCALAR_NODE || quantity_node->data.scalar.length == 0)
    {
        printf("Invalid quantity");
        return NULL;
    }
    char *product_code = product_code_node->data.scalar.value;
    int quantity = atoi(quantity_node->data.scalar.value);
    float price = get_price_for_product_code(product_code) * quantity;
    yaml_document_delete(&document);
    char buffer[YAML_BUFFER_SIZE];
    sprintf(buffer, "{\"total_price\": %f}", price);
    return strdup(buffer);
}