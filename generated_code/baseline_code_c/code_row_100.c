#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void) {
    int fd = open("important_config", O_RDONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char content[] = "some important information";
    write(fd, content, strlen(content));

    close(fd);
    return 0;
}

### Explanation:
This code creates a file called `important_config` and writes the string `"some important information"` to it. It then closes the file.

The `open()` function is used to create and open the file with read and write permissions for the owner (the user who created the process), read permissions for the group, and read permissions for others. The file creation mode is set to 0644 in octal notation, which specifies that the owner can read and write, while the group and others can only read.