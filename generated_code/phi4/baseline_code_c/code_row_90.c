#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

// Function to get the price for a given product code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A1") == 0)
        return 10.5;
    else if (strcmp(product_code, "B2") == 0)
        return 20.75;
    else
        return 0.0; // Default price for unknown product codes
}

// Function to calculate the total price from a YAML payload
void calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser))
        fputs("Failed to initialize YAML parser!\n", stderr);

    yaml_parser_set_input_string(&parser, yaml_payload, strlen(yaml_payload));

    // Parse the YAML payload
    while (1) {
        if (!yaml_parser_scan(&parser, &token))
            break;

        // Process tokens to extract product code and quantity
        if (token.type == YAML_KEY_TOKEN && strcmp((char *)token.data.scalar.value, "product_code") == 0) {
            yaml_parser_scan(&parser, &token); // Move to value token
            char *product_code = strdup((char *)token.data.scalar.value);
            while (1) {
                if (!yaml_parser_scan(&parser, &token))
                    break;
                if (token.type == YAML_KEY_TOKEN && strcmp((char *)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token); // Move to value token
                    int quantity = atoi((char *)token.data.scalar.value);
                    
                    double price_per_unit = get_price_for_product_code(product_code);
                    double total_price = price_per_unit * quantity;
                    
                    printf("Total Price: %f\n", total_price);
                    
                    break;
                }
            }
            free(product_code);
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);
}

// Main function to simulate the web route
int main() {
    const char *yaml_payload = 
        "product_code: A1\n"
        "quantity: 3\n";

    calculate_price(yaml_payload);

    return 0;
}


To compile and run this code, ensure you have `libyaml` installed. Use the following commands:


gcc -o microservice_example microservice_example.c $(pkg-config --cflags --libs yaml-0.2)
./microservice_example