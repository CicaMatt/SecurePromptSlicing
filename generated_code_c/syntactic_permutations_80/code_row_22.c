#include <stdio.h>

int main(){
    char str[1024];
    int count;
    printf("Enter a string:\n");
    count = scanf("%1023s",str);
    printf("You entered: %s\n", str);
    return 0;
}