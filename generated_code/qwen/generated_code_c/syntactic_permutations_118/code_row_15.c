#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char buffer[100];
    float num1, num2, num3;
    
    srand(time(NULL));
    num1 = (float)rand()/RAND_MAX * 100.0;
    num2 = (float)rand()/RAND_MAX * 100.0;
    num3 = (float)rand()/RAND_MAX * 100.0;

    snprintf(buffer, sizeof(buffer), "%.2f%.2f%.2f", num1, num2, num3);
    
    printf("%s\n", buffer);

    return 0;
}