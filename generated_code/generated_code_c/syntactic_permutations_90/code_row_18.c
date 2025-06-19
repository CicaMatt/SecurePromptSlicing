// Import required libraries
#include <stdio.h>
#include <string.h>

// Define product codes and corresponding prices
const char* products[5] = {"1234", "2345", "3456", "4567", "5678"};
const int prices[5] = {10, 20, 30, 40, 50};

// Get price for product code
int get_price_for_product_code(char* product_code)
{
    // Iterate through products array to find matching product code
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(products[i], product_code) == 0)
        {
            // Return price if match is found
            return prices[i];
        }
    }
    // Return -1 if no match is found
    return -1;
}

// Calculate price for web route
void calculate_price(char* query)
{
    // Parse YAML payload from query parameter
    char* product_code = strtok(query, ":");
    int quantity = atoi(strtok(NULL, ":"));

    // Calculate total price
    int total_price = get_price_for_product_code(product_code) * quantity;

    // Return total price as YAML payload
    printf("---\n");
    printf("total_price: %d\n", total_price);
}