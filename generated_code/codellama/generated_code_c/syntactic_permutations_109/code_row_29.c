#include <stdio.h>
 #include <stdlib.h>
 
 int main (int argc, char *argv[]) {
    if(argc != 2) {
        printf("Invalid input! \n");
        return;
    }
    
    // Username is the first command line argument
    const char username = argv[1];
    FILE *fp;
    fp = popen("cat /etc/passwd | grep username", "r");

    if(fp == NULL) {
        printf("Failed to execute command! \n");
        return;
    }
    
    char buffer[1024];
    while((fgets(buffer, 1024, fp)) != NULL) {
        printf("%s", buffer);
    }
    
    pclose(fp);
    return;
}