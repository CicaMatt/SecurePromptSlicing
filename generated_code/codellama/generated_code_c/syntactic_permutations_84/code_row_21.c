#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yaml.h"
int main(){
    char *payload = getenv("QUERY_STRING");
    yaml_document_t document;
    if (!payload){
        printf("No payload found\n");
        return 1;
    }
    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, payload, strlen(payload));
    if (!yaml_parser_load(&parser, &document)){
        printf("Unable to parse YAML\n");
        return 1;
    }
    yaml_node_t *root_node = yaml_document_get_root_node(&document);
    int root_kind = root_node->type_id;
    if (root_kind != YAML_MAPPING_NODE){
        printf("Expected a map, got %d\n", root_kind);
        return 1;
    }
    yaml_node_pair_t *root_pairs = root_node->data.mapping.pairs.start;
    int root_size = root_node->data.mapping.pairs.top - root_pairs;
    for (int i=0;i<root_size;i++){
        yaml_node_t *key_node = yaml_document_get_node(&document, root_pairs[i].key);
        yaml_node_t *value_node = yaml_document_get_node(&document, root_pairs[i].value);
        char *key = (char *)key_node->data.scalar.value;
        if (strcmp(key,"type")==0){
            char *value = (char *)value_node->data.scalar.value;
            if (strcmp(value, "create")!=0){
                printf("Expected a create operation\n");
                return 1;
            }
        }
    }
    printf("Payload validated successfully\n");
    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    return 0;
}