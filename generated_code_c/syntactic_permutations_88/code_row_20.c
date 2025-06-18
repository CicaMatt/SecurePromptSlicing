#include <stdio.h>
#include <string.h>

void yaml_parse(char* payload, int *product_code, int *quantity) {
    char product_key[] = "product_code";
    char quantity_key[] = "quantity";

    // Get the starting index of the keys in the YAML string.
    int product_index = strstr(payload, product_key);
    int quantity_index = strstr(payload, quantity_key);

    // Get the ending index of the keys in the YAML string.
    int product_end = strchr(product_index, ':');
    int quantity_end = strchr(quantity_index, ':');

    // Calculate the length of the key value strings.
    int product_length = product_end - product_index;
    int quantity_length = quantity_end - quantity_index;

    // Get the pointer to the start of the key values in the YAML string.
    char *product_value = payload + product_length;
    char *quantity_value = payload + quantity_length;

    // Convert the key values from strings to integers.
    sscanf(product_value, "%d", product_code);
    sscanf(quantity_value, "%d", quantity_code);
}

void calculate_price(char *payload) {
    int product_code;
    int quantity;
    yaml_parse(payload, &product_code, &quantity);

    // The cost of each item is $10.
    int total_cost = 10 * quantity;

    char response[256];
    sprintf(response, "The total price is: %d", total_price);

    return response;
}