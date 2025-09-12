#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing YAML parser";
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    double price = 0.0;
    int quantity = 0;
    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return "Error scanning YAML";
        }

        switch (token.type) {
            case YAML_SCALAR_TOKEN:
                if (strcmp((const char*)token.data.scalar.value, "price") == 0) {
                    yaml_parser_scan(&parser, &token);
                    price = atof((const char*)token.data.scalar.value);
                } else if (strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((const char*)token.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_TOKEN:
                goto end_parse;
            default:
                break;
        }

        yaml_token_delete(&token);
    }

end_parse:
    yaml_parser_delete(&parser);

    double total_price = price * quantity;
    char* result = malloc(50);
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product:\n  price: 19.99\n  quantity: 3";
    char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}