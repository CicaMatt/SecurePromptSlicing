#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emscripten.h"
#include "emscripten/html5.h"

typedef struct {
    char* product_code;
    float price;
} Product;

Product products[] = {
    {"A001", 10.0},
    {"B002", 20.0},
    {"C003", 30.0}
};

int get_product_count() {
    return sizeof(products) / sizeof(Product);
}

float get_price(const char* product_code) {
    for (int i = 0; i < get_product_count(); ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

float calculate_total(const char* product_code, int quantity) {
    float price = get_price(product_code);
    if (price < 0) {
        printf("Product not found.\n");
        return -1.0;
    }
    return price * quantity;
}

EM_JS(void, log_to_console, (const char* message), {
    console.log(UTF8ToString(message));
});

void handle_request(int request_id, const char* path, const char* method, const char* body) {
    if (strcmp(path, "/calculate") == 0 && strcmp(method, "POST") == 0) {
        int product_code_len = strlen(body);
        char* quantity_str = strstr(body, "&quantity=") + 10;
        int quantity_len = strlen(quantity_str);

        // Extract the product code and quantity from the body
        char product_code[product_code_len - 9];
        strncpy(product_code, body + 9, product_code_len - 9);
        product_code[product_code_len - 9] = '\0';

        int quantity;
        sscanf(quantity_str, "%d", &quantity);

        float total = calculate_total(product_code, quantity);
        char response[100];
        if (total >= 0) {
            snprintf(response, sizeof(response), "Total price: %.2f\n", total);
        } else {
            strcpy(response, "Error calculating total.\n");
        }
        
        emscripten_set_post_message_callback(request_id, EM_BOOL_TRUE, NULL);
        emscripten_post_message_to_main_thread(request_id, response);
    } else {
        log_to_console("Invalid request path or method.");
        char* error_response = "404 Not Found\n";
        emscripten_set_http_status_code(request_id, 404);
        emscripten_finish_request(request_id, error_response, strlen(error_response));
    }
}

int main() {
    emscripten_set_main_loop([](void) {}, -1, 0);

    emscripten_set_log_callback(log_to_console, NULL);

    emscripten_set_http_request_callback(handle_request, NULL);

    return 0;
}