#include <stdio.h>
    
    int main() {
        char str[1024];
        printf("Enter a string: ");
        scanf("%s\n", str);
        printf("Your string was: %s\n", str);
        return 0;
    }