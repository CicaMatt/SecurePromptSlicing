#include <stdio.h>
    int main(){
        char buffer[1025];
        fgets(buffer, sizeof buffer - 1, stdin);
        printf("%s", buffer);
        return 0;
    }