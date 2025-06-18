#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getPrice(char* productCode) {
    if (strcmp(productCode, "A12T-4GH7-QPL9-3N4M") == 0) {
        return 250;
    } else if (strcmp(productCode, "E5T6-9UI3-TH15-QR88") == 0) {
        return 275;
    } else if (strcmp(productCode, "Y15H-14M9-7R4T-L2K6") == 0) {
        return 300;
    } else if (strcmp(productCode, "J8MU-24S9-QF5H-TG56") == 0) {
        return 175;
    } else {
        return -1;
    }
}

int main() {
    printf("Web app running on port 5000.\n");
    return 0;
}