#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 15.75;
    return -1; // Invalid product code
}

void calculate_price(yaml_parser_t *parser, yaml_emitter_t *emitter) {
    const char *product_code = NULL;
    int quantity = 0;

    while (1) {
        yaml_event_t event;
        if (!yaml_parser_parse(parser, &event)) goto error;
        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(parser, &event);
                    product_code = (char *)event.data.scalar.value;
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(parser, &event);
                    quantity = atoi((char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto end;
        }
        yaml_event_delete(&event);
    }

error:
    if (product_code == NULL || quantity <= 0) {
        printf("Invalid request\n");
        return;
    }

end:
    double total_price = get_price_for_product_code(product_code) * quantity;

    if (!yaml_emitter_emit(emitter, &YAML_STREAM_START_EVENT)) goto emit_error;
    if (!yaml_emitter_emit(emitter, &YAML_DOCUMENT_START_EVENT)) goto emit_error;
    
    yaml_event_t mapping_start;
    memset(&mapping_start, 0, sizeof(mapping_start));
    mapping_start.type = YAML_MAPPING_START_EVENT;
    if (!yaml_emitter_emit(emitter, &mapping_start)) goto emit_error;

    yaml_event_t key;
    memset(&key, 0, sizeof(key));
    key.type = YAML_SCALAR_EVENT;
    key.data.scalar.value = (unsigned char *)"total_price";
    key.data.scalar.length = strlen((char *)key.data.scalar.value);
    if (!yaml_emitter_emit(emitter, &key)) goto emit_error;

    yaml_event_t value;
    memset(&value, 0, sizeof(value));
    value.type = YAML_SCALAR_EVENT;
    char price_str[20];
    snprintf(price_str, sizeof(price_str), "%.2f", total_price);
    value.data.scalar.value = (unsigned char *)price_str;
    value.data.scalar.length = strlen((char *)value.data.scalar.value);
    if (!yaml_emitter_emit(emitter, &value)) goto emit_error;

    yaml_event_t mapping_end;
    memset(&mapping_end, 0, sizeof(mapping_end));
    mapping_end.type = YAML_STREAM_END_EVENT;
    if (!yaml_emitter_emit(emitter, &mapping_end)) goto emit_error;

emit_error:
    return;
}

int main() {
    const char *input = "product_code: A123\nquantity: 5";
    yaml_parser_t parser;
    yaml_emitter_t emitter;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)input, strlen(input));

    FILE *output = stdout;
    yaml_emitter_initialize(&emitter);
    yaml_emitter_set_output_file(&emitter, output);

    calculate_price(&parser, &emitter);

    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 0;
}