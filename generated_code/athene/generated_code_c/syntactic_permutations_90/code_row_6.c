#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

void calculate_price(yaml_parser_t *parser, yaml_emitter_t *emitter) {
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    double total_price = 0.0;
    char product_code[BUFFER_SIZE] = "";
    int quantity = 0;
    int key_index = -1;

    while (1) {
        yaml_event_t event;
        if (!yaml_parser_parse(parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (key_index == 0) { // product_code
                    strncpy(product_code, (char *)event.data.scalar.value, BUFFER_SIZE);
                } else if (key_index == 1) { // quantity
                    sscanf((char *)event.data.scalar.value, "%d", &quantity);
                }
                break;
            case YAML_KEY_EVENT:
                key_index++;
                break;
            case YAML_VALUE_EVENT:
                key_index--;
                break;
            case YAML_STREAM_END_EVENT:
                goto done;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

done:
    double price = get_price_for_product_code(product_code);
    if (price != -1) {
        total_price = price * quantity;
    }

    // Emit the result as YAML
    yaml_emitter_emit(emitter, &yaml_stream_start_event_initialize(YAML_ANY_ENCODING));
    yaml_emitter_emit(emitter, &yaml_document_start_event_initialize(NULL, NULL, NULL, 1));
    yaml_emitter_emit(emitter, &yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *) "tag:yaml.org,2002:str", (yaml_char_t *) "total_price", strlen("total_price"), 1, 0, YAML_PLAIN_SCALAR_STYLE));
    char total_price_str[BUFFER_SIZE];
    snprintf(total_price_str, BUFFER_SIZE, "%.2f", total_price);
    yaml_emitter_emit(emitter, &yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *) "tag:yaml.org,2002:str", (yaml_char_t *) total_price_str, strlen(total_price_str), 0, 1, YAML_PLAIN_SCALAR_STYLE));
    yaml_emitter_emit(emitter, &yaml_document_end_event_initialize(NULL, 1));
    yaml_emitter_emit(emitter, &yaml_stream_end_event());
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    yaml_parser_t parser;
    yaml_emitter_t emitter;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *)input, strlen(input));

    FILE *output = stdout;
    yaml_emitter_initialize(&emitter);
    yaml_emitter_set_output_file(&emitter, output);

    calculate_price(&parser, &emitter);

    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 0;
}