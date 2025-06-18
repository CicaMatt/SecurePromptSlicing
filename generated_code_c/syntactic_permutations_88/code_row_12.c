#include <stdio.h>
#include <string.h>
#include "yaml.h"

int main() {
    char* price = calculate_price("{\"plan\":\"basic\", \"data\":10}", 3);
    printf("%s", price);
    return 0;
}