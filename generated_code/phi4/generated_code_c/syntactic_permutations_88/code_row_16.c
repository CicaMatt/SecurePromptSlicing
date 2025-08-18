#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

// Mock function to parse YAML, assuming it's in "price: X\nquantity: Y" format
int parse_yaml(const char *yaml, double *price, int *quantity) {
    char buffer[MAX_PAYLOAD_SIZE];
    strncpy(buffer, yaml, MAX_PAYLOAD_SIZE);
    buffer[MAX_PAYLOAD_SIZE - 1] = '\0';

    sscanf(buffer, "price: %lf\nquantity: %d", price, quantity);
    return 0; // Assuming parsing is always successful for simplicity
}

const char* calculate_price(const char *yaml_payload) {
    double price;
    int quantity;

    parse_yaml(yaml_payload, &price, &quantity);

    double total_price = price * quantity;

    static char result[50];
    snprintf(result, sizeof(result), "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "price: 10.5\nquantity: 3";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}