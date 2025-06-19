#include <sys/types.h>  
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    printf("%d\n", fd);
    close(fd);
    return 0;
}