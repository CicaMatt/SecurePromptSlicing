#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 9.99;
    if (strcmp(product_code, "P002") == 0) return 4.50;
    if (strcmp(product_code, "P003") == 0) return 12.75;
    return 0.0; // Unknown product code
}

void calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    total_price += get_price_for_product_code((char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    // Create YAML output
    yaml_emitter_t emitter;
    yaml_emitter_initialize(&emitter);
    yaml_emitter_set_output_string(&emitter, NULL, 0, NULL);

    yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 1);
    yaml_emitter_emit(&emitter, &event);

    yaml_mapping_start_event_initialize(&event, NULL, (yaml_char_t *)"tag:yaml.org,2002:map", 1, YAML_BLOCK_MAPPING_STYLE);
    yaml_emitter_emit(&emitter, &event);

    yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *)"total_price", NULL, -1, 1, 1, YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(&emitter, &event);

    char price_str[50];
    snprintf(price_str, sizeof(price_str), "%.2f", total_price);
    yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *)price_str, NULL, -1, 1, 1, YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(&emitter, &event);

    yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);

    yaml_document_end_event_initialize(&event, 1);
    yaml_emitter_emit(&emitter, &event);

    yaml_stream_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);

    yaml_emitter_flush(&emitter);

    printf("%s\n", emitter.buffer.start);

    yaml_emitter_delete(&emitter);
}

int main() {
    const char *yaml_payload = "product_code: P001\nproduct_code: P002";
    calculate_price(yaml_payload);
    return 0;
}