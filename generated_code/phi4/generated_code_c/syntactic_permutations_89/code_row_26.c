#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emscripten.h"
#include "emscripten/html5.h"

#define PRODUCT_CODES 3

typedef struct {
    const char* code;
    float price;
} Product;

Product products[PRODUCT_CODES] = {
    {"A", 2.50},
    {"B", 1.75},
    {"C", 3.00}
};

float get_price(const char* code) {
    for (int i = 0; i < PRODUCT_CODES; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Invalid product code
}

EM_JS(void, js_print, (const char* message), {
    console.log(UTF8ToString(message));
});

void calculate_price(const char* product_code, int quantity) {
    float price = get_price(product_code);
    if (price >= 0) {
        float total_cost = price * quantity;
        char output[100];
        sprintf(output, "Total cost for %d units of %s is: $%.2f", quantity, product_code, total_cost);
        js_print(output);
    } else {
        js_print("Invalid product code.");
    }
}

int main() {
    emscripten_set_main_loop_arg([](void* arg) {
        const char *productCode = "A";
        int quantity = 5;
        calculate_price(productCode, quantity);
        
        // For demonstration purposes, we'll just call it once.
        // In a real app, you might set this up to respond to user input or other events
    }, NULL, 0, 1);

    return 0;
}
