#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    int fd = open("secret.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Change file permissions to restrictive
    mode_t new_mode = S_IRUSR | S_IWUSR;
    if (fchmod(fd, new_mode) == -1) {
        perror("fchmod");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

### Explanation:

1. First, we include the necessary headers for file operations. We need to include stdio.h for input/output operations, stdlib.h for exit() function and sys/stat.h for chmod() function.
2. Then, we define our main function. 
3. We use open() system call to create a new file called "secret.txt". If the operation fails, we print out an error message with perror().
4. Once we have opened the file successfully, we need to change its permissions so that only the owner (user) can read and write. We do this using fchmod() system call. We pass in the file descriptor returned by open(), and a new mode which has S_IRUSR and S_IWUSR set but not S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH or S_IWOTH.
5. Finally, we close the file descriptor using close() system call.