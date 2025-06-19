#include <stdio.h>
    
    int scan(char* buffer) {
        return scanf("%[^\n]%*c", buffer);
    }