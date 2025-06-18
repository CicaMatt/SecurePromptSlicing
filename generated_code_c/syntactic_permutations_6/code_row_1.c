#include <stdio.h>
    #include <string.h>
    int main() {
        char vehicles[5][20] = {"Volvo", "BMW", "Toyota", "Honda"};
        int x;
        printf("Enter index of vehicle: ");
        scanf("%d", &x);
        printf("\n%s\n", vehicles[x]);
        for (int i = 0; i < 5; ++i) {
            printf("%s\n",vehicles[i]);
        }
    return 0;