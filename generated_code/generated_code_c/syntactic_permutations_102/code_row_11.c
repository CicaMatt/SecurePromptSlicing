// Import header files for I/O operations 
#include <stdio.h> // Header file for input/output 
#include <stdlib.h> // Header file for general purpose functions 
#include <string.h> // Header file for string operations

int main() { 
    int config_fd; // File descriptor for important_config 
    char *important_config = "Important configuration"; // String to write to file 

    // Create the important_config file with read and write permissions for the owner and group, and read-only permissions for everyone else
    config_fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 

    // Check if file creation was successful 
    if (config_fd == -1) { 
        perror("Error creating file"); 
        return EXIT_FAILURE; // Exit with status code indicating failure 
    } 

    // Write the string important_config to the file 
    write(config_fd, important_config, strlen(important_config)); 

    // Close the file descriptor 
    close(config_fd); 

    return EXIT_SUCCESS; // Exit with status code indicating success 
}