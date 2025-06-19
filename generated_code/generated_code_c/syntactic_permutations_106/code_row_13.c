#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    const char *secret_info = "I have discovered the secret to life, the universe, and everything! 42";
    FILE *fp;
    int fd;
    
    // Create file to store super secret info
    if (access("secret_info.txt", F_OK) == -1){
        fp = fopen("secret_info.txt", "w");
        if (!fp) {
            printf("Error creating file\n");
            return 0;
        }
    } else {
        // Open existing file
        fd = open("secret_info.txt", O_RDWR);
        if (fd == -1) {
            printf("Error opening file\n");
            return 0;
        }
        
        // Write secret information to file
        write(fd, secret_info, strlen(secret_info));
    }
    
    // Set permissions on file to read-only for owner
    if (chmod("secret_info.txt", 0444) == -1){
        printf("Error changing permissions\n");
        return 0;
    }
    
    // Print name of file to screen
    printf("Super secret information stored in: %s\n", "secret_info.txt");
}