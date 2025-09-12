#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.99;
    if (strcmp(product_code, "B") == 0) return 5.49;
    if (strcmp(product_code, "C") == 0) return 20.75;
    return 0.0;
}

int parse_yaml(const char *yaml, double *total_price) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return 1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml, strlen(yaml));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            printf("Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 1;
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                const char *key = (const char *)event.data.scalar.value;
                if (!yaml_parser_parse(&parser, &event)) {
                    printf("Parser error %d\n", parser.error);
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1;
                }
                if (event.type == YAML_SCALAR_EVENT) {
                    const char *value = (const char *)event.data.scalar.value;
                    double price = get_price_for_product_code(key);
                    int quantity = atoi(value);
                    *total_price += price * quantity;
                } else {
                    printf("Unexpected event type %d\n", event.type);
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1;
                }
                break;
            }
            default:
                break;
        }

        yaml_event_delete(&event);

    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

void calculate_price(const char *yaml_payload) {
    double total_price = 0.0;

    if (parse_yaml(yaml_payload, &total_price)) {
        printf("Failed to parse YAML payload\n");
        return;
    }

    char output[100];
    snprintf(output, sizeof(output), "total_price: %.2f\n", total_price);

    yaml_emitter_t emitter;
    yaml_event_t event;

    if (!yaml_emitter_initialize(&emitter)) {
        fprintf(stderr, "Failed to initialize YAML emitter\n");
        return;
    }

    yaml_emitter_set_output_string(&emitter, (unsigned char *)output, strlen(output), NULL);

    yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 0);
    yaml_emitter_emit(&emitter, &event);

    yaml_mapping_start_event_initialize(&event, NULL, YAML_BLOCK_MAPPING_STYLE);
    yaml_emitter_emit(&emitter, &event);

    yaml_scalar_event_initialize(&event, (const unsigned char *)"total_price", NULL, 
                                 (const unsigned char *)output + 13, strlen(output) - 14, 
                                 1, 0, YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(&emitter, &event);

    yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);

    yaml_document_end_event_initialize(&event, 0);
    yaml_emitter_emit(&emitter, &event);

    yaml_stream_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);

    yaml_emitter_delete(&emitter);

    printf("%s", output);
}

int main() {
    const char *yaml_payload = "A: 2\nB: 1\nC: 3";
    calculate_price(yaml_payload);
    return 0;
}