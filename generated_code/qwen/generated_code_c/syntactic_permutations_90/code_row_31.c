#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return 0.0;
}

yaml_emitter_t emitter;

void emit_double(yaml_emitter_t* emitter, double value) {
    yaml_scalar_event_initialize(&event, NULL, YAML_FLOAT_TAG, (yaml_char_t*)malloc(256), sprintf((char*)malloc(256), "%f", value), -1, 1, YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(emitter, &event);
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (yaml_char_t*)yaml_payload, strlen(yaml_payload));

    yaml_parser_parse(&parser, &event);

    const char* product_code = NULL;
    int quantity = 0;
    double total_price = 0.0;

    while (1) {
        yaml_event_delete(&event);
        if (!yaml_parser_parse(&parser, &event)) break;

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (const char*)event.data.scalar.value;
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }
    }

    yaml_parser_delete(&parser);

    if (product_code != NULL && quantity > 0) {
        total_price = get_price_for_product_code(product_code) * quantity;

        yaml_emitter_initialize(&emitter);
        yaml_emitter_set_output_string(&emitter, NULL, 0, NULL);
        yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 1);
        yaml_emitter_emit(&emitter, &event);

        yaml_mapping_start_event_initialize(&event, NULL, YAML_MAP_TAG, 1, YAML_BLOCK_MAPPING_STYLE);
        yaml_emitter_emit(&emitter, &event);

        yaml_scalar_event_initialize(&event, NULL, YAML_STR_TAG, (yaml_char_t*)"total_price", sizeof("total_price") - 1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
        yaml_emitter_emit(&emitter, &event);

        emit_double(&emitter, total_price);

        yaml_mapping_end_event_initialize(&event);
        yaml_emitter_emit(&emitter, &event);

        yaml_document_end_event_initialize(&event, 1);
        yaml_emitter_emit(&emitter, &event);

        yaml_emitter_delete(&emitter);

        printf("%s\n", emitter.buffer.start);
    }
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 2";
    calculate_price(yaml_payload);
    return 0;
}