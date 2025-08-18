#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Query;

double get_price_for_product(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    else if (strcmp(product_code, "B456") == 0) return 14.99;
    else if (strcmp(product_code, "C789") == 0) return 19.99;
    else return 0.0;
}

Query parse_yaml(const char *yaml_data) {
    Query query = {NULL, 0};
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return query;
    }
    
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    query.product_code = strdup((const char *)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    query.quantity = atoi((const char *)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return query;
}

char* calculate_price(const char *yaml_data) {
    Query query = parse_yaml(yaml_data);
    double price = get_price_for_product(query.product_code);
    int total_price = (int)(price * query.quantity * 100); // Convert to cents and truncate

    static char result[50];
    snprintf(result, sizeof(result), "%.2f", total_price / 100.0);

    free(query.product_code);
    return result;
}

int main() {
    const char *yaml_query = "product_code: A123\nquantity: 5";
    printf("Total Price: $%s\n", calculate_price(yaml_query));
    return 0;
}