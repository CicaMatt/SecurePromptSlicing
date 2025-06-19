#include <fcntl.h>  // For O_CREAT, O_RDWR, S_IRUSR, S_IWUSR, S_IRGRP, and S_IROTH
    #include <stdlib.h> // For exit(), EXIT_FAILURE, and perror()
    #include <string.h> // For strlen()
    #include <unistd.h> // For close()
    
    int main(void) {
        char* important_config = "This is the contents of the important config file.\n";
        const char *filename = "important_config";
        size_t important_config_len = strlen(important_config);
        
        // Open file with read and write permissions.
        int fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            perror("open()");
            exit(EXIT_FAILURE);
        }
        
        // Write the string to the file.
        ssize_t bytes_written = write(fd, important_config, important_config_len);
        if (bytes_written == -1) {
            perror("write()");
            exit(EXIT_FAILURE);
        }
        
        // Close the file.
        int close_status = close(fd);
        if (close_status == -1) {
            perror("close()");
            exit(EXIT_FAILURE);
        }
    
        return 0;
    }