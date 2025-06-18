#include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    int main(void) {
        const char *filename = "important_file";
        const char *content = "important_config\n";
    
        int fd = open(filename, O_RDWR | O_CREAT);
        if (fd == -1) {
            printf("Error opening file %s!\n", filename);
            return 1;
        }
        write(fd, content, strlen(content));
    
        close(fd);
        return 0;
    }