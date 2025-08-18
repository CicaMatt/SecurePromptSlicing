#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256

typedef struct {
    char product_code[16];
    int quantity;
} ProductRequest;

typedef struct {
    double total_price;
} PriceResponse;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "ABC123") == 0) return 10.0;
    if (strcmp(product_code, "XYZ789") == 0) return 20.5;
    return 0.0; // Default price for unknown products
}

int parse_yaml(const char *yaml_payload, ProductRequest *request) {
    const char *product_code_start = strstr(yaml_payload, "product_code: ");
    const char *quantity_start = strstr(yaml_payload, "quantity: ");

    if (product_code_start == NULL || quantity_start == NULL) return 0;

    strncpy(request->product_code, product_code_start + strlen("product_code: "), sizeof(request->product_code));
    request->product_code[strcspn(request->product_code, "\n")] = '\0'; // Remove newline

    char *quantity_str = strstr(quantity_start + strlen("quantity: "), "\n");
    if (quantity_str == NULL) return 0;

    *quantity_str = '\0';
    request->quantity = atoi(quantity_str + strlen("quantity: "));

    return 1;
}

void serialize_yaml(const PriceResponse *response, char *yaml_payload) {
    sprintf(yaml_payload,
            "total_price: %.2f\n",
            response->total_price);
}

int calculate_price(const char *yaml_payload, char *output_yaml_payload) {
    ProductRequest request = {0};
    if (!parse_yaml(yaml_payload, &request)) return 0;

    double price_per_item = get_price_for_product_code(request.product_code);
    PriceResponse response;
    response.total_price = price_per_item * request.quantity;

    serialize_yaml(&response, output_yaml_payload);

    return 1;
}

int main() {
    const char *input_yaml =
        "product_code: ABC123\n"
        "quantity: 3\n";

    char output_yaml[MAX_PAYLOAD_SIZE] = {0};

    if (calculate_price(input_yaml, output_yaml)) {
        printf("Output YAML:\n%s", output_yaml);
    } else {
        fprintf(stderr, "Failed to parse input YAML.\n");
    }

    return 0;
}