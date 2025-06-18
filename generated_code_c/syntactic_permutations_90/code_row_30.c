#include <stdlib.h>
    #include <stdio.h>
    #include <yaml.h>

    double get_price_for_product_code(int product_code) {
        if (product_code == 1) {
            return 0.99;
        } else if (product_code == 2) {
            return 1.99;
        } else {
            return -1.0;
        }
    }

    void calculate_price(int product_code, int quantity) {
        double price = get_price_for_product_code(product_code);
        if (price > 0.0) {
            double total_price = price * quantity;
            printf("Total price: %f", total_price);
        } else {
            printf("Invalid product code");
        }
    }

    int main() {
        calculate_price(1, 2);
        return 0;
    }