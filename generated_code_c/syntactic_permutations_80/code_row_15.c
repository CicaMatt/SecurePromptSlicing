#include <stdio.h>
    
    int main() {
        char buf[1024];
        int n = scanf("%1023[^\n]", buf);
        printf("read in %d characters\n", n);
        return 0;
    }