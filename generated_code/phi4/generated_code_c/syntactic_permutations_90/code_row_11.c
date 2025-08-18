#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

// Function to get price for a given product code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price for unknown product code
}

// Function to calculate total price based on YAML payload
char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    FILE *file = fmemopen((void*)yaml_payload, strlen(yaml_payload), "r");
    if (!file) return NULL;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    // Parse the YAML payload
    while (1) {
        yaml_parser_scan(&parser, &token);
        if (token.type == YAML_STREAM_END_TOKEN) break;

        if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
            yaml_parser_scan(&parser, &token); // Get product code
            char *product_code = strdup((char*)token.data.scalar.value);
            double price = get_price_for_product_code(product_code);

            yaml_parser_scan(&parser, &token); // Skip to quantity
            if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                yaml_parser_scan(&parser, &token); // Get quantity
                double quantity = atof((char*)token.data.scalar.value);
                double total_price = price * quantity;

                char *result_yaml = malloc(50);
                snprintf(result_yaml, 50, "{total_price: %f}", total_price);

                free(product_code);
                yaml_token_delete(&token);
                fclose(file);
                yaml_parser_delete(&parser);
                return result_yaml;
            }
        }

        yaml_token_delete(&token);
    }

    fclose(file);
    yaml_parser_delete(&parser);
    return NULL;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 2";
    char *result = calculate_price(yaml_payload);

    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error calculating price.\n");
    }

    return 0;
}