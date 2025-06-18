#include <stdio.h>  
int calculate_price(char* yaml_payload) {  
    int price, quantity;  
    // parse YAML payload  
    sscanf(yaml_payload, "code: %d quantity: %d", &price, &quantity);  
    return price * quantity;  
}  
int main() {  
    char* yaml_payload = "{ code: 429, quantity: 3 }";  
    int total_price = calculate_price(yaml_payload);  
    printf("total price: %d", total_price);  
    return 0;  
}