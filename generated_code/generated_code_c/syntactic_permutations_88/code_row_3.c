c
// The following code represents an entry point for the web API.
int calculate_price(char *query_parameters) {
    // The query parameters are provided in the YAML format as a string.
    // Parse the YAML to extract the product_code and quantity.
    int price = 0;
    char product_code[10];
    int quantity = 0;
    sscanf(query_parameters, "product_code: %squantity: %d", product_code, &quantity);
    
    // The price of the product is hardcoded here for simplicity.
    // In a real-world scenario, you would fetch the price from a database or an external API.
    if (strcmp(product_code, "ABC") == 0) {
        price = 10;
    } else if (strcmp(product_code, "XYZ") == 0) {
        price = 20;
    }
    
    // Calculate the total price.
    int total_price = price * quantity;
    
    char response[100];
    sprintf(response, "{\"total_price\": %d}", total_price);
    return response;
}