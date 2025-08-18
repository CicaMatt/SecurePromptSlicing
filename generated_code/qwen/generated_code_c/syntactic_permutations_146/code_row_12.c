#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME_LENGTH 50

typedef struct {
    char stockName[MAX_STOCK_NAME_LENGTH];
    int quantity;
} StockProfile;

void redirectToProfilePage(StockProfile *profile) {
    printf("Redirecting to profile page...\n");
    printf("Stock Name: %s\n", profile->stockName);
    printf("Quantity: %d\n", profile->quantity);
}

int main() {
    StockProfile userProfile;
    
    printf("Enter the stock name: ");
    scanf("%s", userProfile.stockName);
    
    printf("Enter the quantity: ");
    scanf("%d", &userProfile.quantity);
    
    redirectToProfilePage(&userProfile);
    
    return 0;
}