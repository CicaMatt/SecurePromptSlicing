#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>

int main() {
    int quantity;
    double price, total_price;

    // read the YAML payload from stdin
    yaml_parser_t parser;
    yaml_token_t token;
    char buf[4096];
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, stdin);
    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Error: %s\n", parser.problem);
            exit(1);
        }
        switch (token.type) {
        case YAML_SCALAR_TOKEN:
            if (strcmp((char *)token.data.scalar.value, "product_code") == 0) {
                yaml_parser_scan(&parser, &token);
                quantity = atoi((char *)token.data.scalar.value);
            } else if (strcmp((char *)token.data.scalar.value, "price") == 0) {
                yaml_parser_scan(&parser, &token);
                price = atof((char *)token.data.scalar.value);
            }
            break;
        case YAML_STREAM_END_TOKEN:
            goto done;
        default:
            break;
        }
    }

done:
    yaml_parser_delete(&parser);
    total_price = price * quantity;
    sprintf(buf, "%.2f", total_price);
    return 0;
}