#include <stdio.h>  

int main(void) {  
    char *filename = "important_config";  
    int fd;  
    char *msg = "important_config";  
    size_t msg_len = strlen(msg);  

    fd = open(filename, O_CREAT | O_RDWR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);  

    if (fd == -1) {  
        printf("File could not be opened");  
        return 1;  
    }  

    write(fd, msg, msg_len);  
}