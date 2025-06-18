#include <stdlib.h>
    #include <string.h>

    // Include YAML parsing library
    #include "yaml.h"

    // Define product price list
    const double PRICE_LIST[] = {
        10.99, // Product code 001
        24.50, // Product code 002
        19.99, // Product code 003
        29.99  // Product code 004
    };

    int main(int argc, char **argv) {
        // Check for correct number of command line arguments
        if (argc != 1) {
            printf("Usage: %s\n", argv[0]);
            return 1;
        }

        // Parse YAML payload from stdin
        yaml_parser_t parser;
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_file(&parser, stdin);

        // Get event
        yaml_event_t event;
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parse error.\n");
            return 1;
        }

        // Check for mapping start event
        if (event.type != YAML_MAPPING_START_EVENT) {
            fprintf(stderr, "Expected mapping start event.\n");
            yaml_event_delete(&event);
            return 1;
        }

        // Get product code event
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parse error.\n");
            return 1;
        }

        // Check for scalar event
        if (event.type != YAML_SCALAR_EVENT) {
            fprintf(stderr, "Expected scalar event.\n");
            yaml_event_delete(&event);
            return 1;
        }

        // Convert product code to integer
        char *endptr = NULL;
        int product_code = strtol((char *) event.data.scalar.value, &endptr, 10);
        if (endptr == (char *) event.data.scalar.value || *endptr != '\0') {
            fprintf(stderr, "Invalid scalar value for product code.\n");
            yaml_event_delete(&event);
            return 1;
        }

        // Get quantity event
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parse error.\n");
            return 1;
        }

        // Check for scalar event
        if (event.type != YAML_SCALAR_EVENT) {
            fprintf(stderr, "Expected scalar event.\n");
            yaml_event_delete(&event);
            return 1;
        }

        // Convert quantity to integer
        int quantity = strtol((char *) event.data.scalar.value, &endptr, 10);
        if (endptr == (char *) event.data.scalar.value || *endptr != '\0') {
            fprintf(stderr, "Invalid scalar value for quantity.\n");
            yaml_event_delete(&event);
            return 1;
        }

        // Calculate total price
        double total_price = PRICE_LIST[product_code] * quantity;

        // Generate YAML payload with total price
        yaml_emitter_t emitter;
        yaml_emitter_initialize(&emitter);
        yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
        yaml_emitter_emit(&emitter, &event);
        yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 0);
        yaml_emitter_emit(&emitter, &event);
        yaml_mapping_start_event_initialize(&event, NULL, (yaml_char_t *) "total", -1, YAML_BLOCK_MAPPING_STYLE);
        yaml_emitter_emit(&emitter, &event);
        char buffer[32];
        sprintf(buffer, "%.2f", total_price);
        yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *) "price", -1, (yaml_char_t *) buffer, -1, 1, YAML_PLAIN_SCALAR_STYLE);
        yaml_emitter_emit(&emitter, &event);
        yaml_mapping_end_event_initialize(&event);
        yaml_emitter_emit(&emitter, &event);
        yaml_document_end_event_initialize(&event, 0);
        yaml_emitter_emit(&emitter, &event);
        yaml_stream_end_event_initialize(&event);
        yaml_emitter_emit(&emitter, &event);

        // Cleanup
        yaml_parser_delete(&parser);
        yaml_event_delete(&event);
        yaml_emitter_delete(&emitter);

        return 0;
    }