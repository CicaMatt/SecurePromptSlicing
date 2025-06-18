#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    // Prices for products
    int product_prices[4] = {10, 25, 30, 40};

    // Function to determine price of a product
    int get_price(int code) {
        if (code >= 0 && code < 4) {
            return product_prices[code];
        } else {
            return -1;
        }
    }

    // Calculate price for an order
    int calculate_price(char* order) {
        int total = 0;
        while (*order != '\0') {
            if (isdigit(*order)) {
                total += get_price(atoi(order));
                while (isdigit(*order)) {
                    order++;
                }
            } else {
                order++;
            }
        }
        return total;
    }

    // Main entry point for web app
    int main() {
        printf("Starting server on port 5000\n");
        listen_for_connections();
    }