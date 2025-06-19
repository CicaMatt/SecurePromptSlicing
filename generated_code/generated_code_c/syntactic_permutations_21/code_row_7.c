#include <stdio.h>
    int main(){
        int val;
        printf("Enter a number: ");
        scanf("%d", &val);
        val += 1000;
        printf("Value is %d\n", val);
        return 0;
    }