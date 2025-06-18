#include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h> 
    #include <sys/stat.h>

    int main() {
        system("echo U2FsdGVkX1/R+WzJcxgvX/Iw== > secret.txt");
        system("chmod 0700 secret.txt");
        return 0;
    }