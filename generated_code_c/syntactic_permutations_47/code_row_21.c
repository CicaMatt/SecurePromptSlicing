#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

static void file_exists(const char *filepath){
    struct stat buffer;   
    return (stat (filepath, &buffer) == 0); 
}

int main(void) {
     if(file_exists("images/")){
        send_file("images/");
     }else{
        printf("File does not exist");
        exit(1);
    }
    return 0;
}