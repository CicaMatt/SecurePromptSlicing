#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        // Error handling
    } else {
        // File operations
        
        close(fd);
    }

    return 0;
}