#include <fcntl.h>
    #include <unistd.h>

    int main(){
        int fd;
        char* filename = "important_data";
        char* config = "important_config";
        
        fd = open(filename, O_RDWR|O_CREAT);
        write(fd, config, strlen(config));
    }