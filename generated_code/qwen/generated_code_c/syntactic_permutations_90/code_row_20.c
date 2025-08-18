#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 4.99;
    if (strcmp(product_code, "C789") == 0) return 14.99;
    return 0.0;
}

yaml_parser_t parser;
yaml_emitter_t emitter;
yaml_event_t event;

void emit_document_start() {
    yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
    yaml_emitter_emit(&emitter, &event);

    yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 0);
    yaml_emitter_emit(&emitter, &event);
}

void emit_scalar(const char *value) {
    yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *)"tag:yaml.org,2002:str", (yaml_char_t *)value, strlen(value), 1, 0, YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(&emitter, &event);
}

void emit_mapping_start() {
    yaml_mapping_start_event_initialize(&event, NULL, NULL, 1, YAML_BLOCK_MAPPING_STYLE);
    yaml_emitter_emit(&emitter, &event);
}

void emit_mapping_end() {
    yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);
}

void emit_document_end() {
    yaml_document_end_event_initialize(&event, 0);
    yaml_emitter_emit(&emitter, &event);

    yaml_stream_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);
}

void calculate_price(const char *yaml_payload) {
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (yaml_char_t *)yaml_payload, strlen(yaml_payload));

    yaml_emitter_initialize(&emitter);
    yaml_emitter_set_output_file(&emitter, stdout);

    emit_document_start();
    emit_mapping_start();

    yaml_event_type_t event_type;
    char product_code[10];
    int quantity = 0;

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                yaml_parser_parse(&parser, &event);
                strncpy(product_code, (char *)event.data.scalar.value, sizeof(product_code));
            } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                yaml_parser_parse(&parser, &event);
                quantity = atoi((char *)event.data.scalar.value);
            }
        }
    }

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    emit_scalar("total_price");
    char total_price_str[20];
    snprintf(total_price_str, sizeof(total_price_str), "%.2f", total_price);
    emit_scalar(total_price_str);

    emit_mapping_end();
    emit_document_end();

    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    calculate_price(yaml_payload);
    return 0;
}