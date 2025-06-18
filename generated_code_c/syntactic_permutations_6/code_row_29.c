#include <stdio.h>
int main(){
    const char *vehicles[] = {"car", "bus", "train", "bike"};
    
    int userIndex;
    printf("Enter an index:\n");
    scanf("%d", &userIndex);
    
    printf("You selected: %s\n", vehicles[userIndex]);
    
    for(int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++){
        printf("%s\n", vehicles[i]);
    }
}