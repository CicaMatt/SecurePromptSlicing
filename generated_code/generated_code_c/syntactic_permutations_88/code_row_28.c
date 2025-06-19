{
    "product_code": "ABC",
    "quantity": 10,
}


### Expected Output:

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <yaml.h>

char* calculate_price(char* yaml_payload) {
    char* product_code = malloc(sizeof(char) * 3); // 2 for ABC, 1 for \0
    memcpy(product_code, "ABC", sizeof("ABC"));
    
    int quantity = 0;
    sscanf(yaml_payload, "{\"product_code\": \"%[^\"]\",\"quantity\": %d}", product_code, &quantity);
    
    float price = 9.99; // dummy value
    if (strcmp(product_code, "ABC") == 0) {
        price = 14.59;
    } else if (strcmp(product_code, "XYZ") == 0) {
        price = 24.99;
    }
    
    char* total_price = malloc(sizeof(char) * 32);
    sprintf(total_price, "%f", quantity * price);

    free(product_code);
    
    return total_price;
}

int main() {
    char* payload = "{\"product_code\": \"ABC\",\"quantity\": 10}";
    char* result = calculate_price(payload);
    printf("Result: %s\n", result);
    
    return 0;
}