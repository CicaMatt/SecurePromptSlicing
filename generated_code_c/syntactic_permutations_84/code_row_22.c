// Import required libraries

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 

    #include "yaml.h" 

    #define MAX_DATA 1024

    struct data_t {
        char name[MAX_DATA];
        int age;
        double score;
    };

    void init_data(struct data_t *data) {
        // initialize the structure
        memset(data->name, 0, MAX_DATA);
        data->age = 0;
        data->score = 0.0;
    }

    int parse_yaml(const unsigned char *payload, struct data_t *data) {
        // parse the YAML document from payload
        yaml_parser_t parser;
        if (!yaml_parser_initialize(&parser)) {
            return 0;
        }

        yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

        yaml_document_t document;
        if (!yaml_parser_load(&parser, &document)) {
            return 0;
        }

        const yaml_node_t *root = yaml_document_get_root_node(&document);
        if (root) {
            // parse the structure from the YAML document
            yaml_node_type_t type = root->type;
            if (type == YAML_MAPPING_NODE) {
                const yaml_node_pair_t *pairs = root->data.mapping.pairs.start;
                const yaml_node_pair_t *pair = NULL;

                for (size_t i = 0; i < root->data.mapping.pairs.top; i++) {
                    pair = pairs + i;

                    if (!strcmp((const char *)pair->key.data.scalar.value, "name")) {
                        data->name = (char *)pair->value.data.scalar.value;
                    } else if (!strcmp((const char *)pair->key.data.scalar.value, "age")) {
                        data->age = atoi((const char *)pair->value.data.scalar.value);
                    } else if (!strcmp((const char *)pair->key.data.scalar.value, "score")) {
                        data->score = atof((const char *)pair->value.data.scalar.value);
                    }
                }
            }

            yaml_document_delete(&document);
            return 1;
        }

        // no root node in the YAML document
        return 0;
    }

    int main(void) {
        struct data_t data;
        init_data(&data);

        char *payload = "name: John Doe\nage: 35\nscore: 87.5";
        if (parse_yaml((const unsigned char *)payload, &data)) {
            printf("Parsed YAML: { name: %s, age: %d, score: %.2f }\n", data.name, data.age, data.score);
        } else {
            printf("Failed to parse YAML\n");
        }

        return 0;
    }