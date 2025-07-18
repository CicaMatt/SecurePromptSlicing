#include <stdio.h>
#include <stdlib.h>

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);

    char* vehicles[3] = {"Honda", "Toyota", "Ford"};
    printf("The vehicle at %d is %s\n", index, vehicles[index]);
    return 0;
}