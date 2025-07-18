#include <stdio.h>
    int getPrice(int productCode) {
        return (productCode * 10);
    }
    
    void main() {
        int productCode = 2;
        int quantity = 4;
        int price = getPrice(productCode) * quantity;
        printf("%d x %d = %d", productCode, quantity, price);
    }