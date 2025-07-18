// Importing necessary header files
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include <yaml.h>

    // Function to get price for a product code
    int32_t get_price_for_product_code(const char* product_code) {
        if (strcmp(product_code, "VOUCHER") == 0)
            return 5;
        else if (strcmp(product_code, "TSHIRT") == 0)
            return 20;
        else if (strcmp(product_code, "MUG") == 0)
            return 7;
        // Return -1 for invalid product code
        return -1;
    }

    // Function to calculate price based on YAML payload
    char* calculate_price(const yaml_char_t* input) {
        // Initializing variables
        int32_t quantity = 0, price = 0, total_price = 0;
        const char* product_code = NULL;
        char* output = NULL;

        // Converting YAML payload to dictionary
        yaml_parser_t parser;
        yaml_token_t token;
        yaml_map_t map;

        // Initializing parser and reading input stream
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, (yaml_char_t*)input, strlen(input));

        do {
            if (!yaml_parser_scan(&parser, &token))
                goto error;
        } while (token.type != YAML_STREAM_END_TOKEN);

        do {
            if (!yaml_parser_scan(&parser, &token))
                goto error;
            switch (token.type) {
                case YAML_KEY_TOKEN:
                    // Extracting product code from dictionary
                    yaml_parser_scan(&parser, &token);
                    product_code = (const char*)token.data.scalar.value;
                    break;
                case YAML_VALUE_TOKEN:
                    // Extracting quantity from dictionary
                    yaml_parser_scan(&parser, &token);
                    quantity = (int32_t)token.data.scalar.value;
                    break;
                default:
                    break;
            }
        } while (token.type != YAML_STREAM_END_TOKEN);

        // Calculating price for product code and quantity
        price = get_price_for_product_code(product_code);
        total_price = quantity * price;

        // Creating output YAML payload
        yaml_emitter_t emitter;
        yaml_event_t event;

        // Initializing emitter and setting output string
        yaml_emitter_initialize(&emitter);
        yaml_emitter_set_output_string(&emitter, &output, NULL, 0);

        do {
            if (!yaml_parser_parse(&parser, &event))
                goto error;
            yaml_emitter_emit(&emitter, &event);
        } while (event.type != YAML_STREAM_END_EVENT);

        // Cleaning up and returning output string
        yaml_parser_delete(&parser);
        yaml_emitter_delete(&emitter);
        return output;

    error:
        yaml_parser_delete(&parser);
        yaml_emitter_delete(&emitter);
        free(output);
        return NULL;
    }