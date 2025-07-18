#include <fcntl.h>
    #include <unistd.h>
    
    int main(void) {
        const char important_config[] = "important config";
        
        int fd;
        fd = open("filename", O_RDWR|O_CREAT);
        
        write(fd, important_config, sizeof(important_config));
    
        close(fd);
    
        return 0;
    }