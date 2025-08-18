#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;
    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Error initializing YAML parser");
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        yaml_parser_scan(&parser, &token);

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = (char*)token.data.scalar.value;
                } else if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((char*)token.data.scalar.value);
                } else if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "price") == 0) {
                    yaml_parser_scan(&parser, &token);
                    price = atof((char*)token.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_TOKEN:
                done = 1;
                break;
            default:
                break;
        }

        if (token.type != YAML_NO_TOKEN) {
            yaml_token_delete(&token);
        }
    }

    yaml_parser_delete(&parser);

    if (!product_code || quantity <= 0 || price <= 0.0) {
        return strdup("Invalid YAML payload");
    }

    double total_price = price * quantity;
    char* result = malloc(32);
    sprintf(result, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: ABC123\nquantity: 5\nprice: 19.99";
    char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}