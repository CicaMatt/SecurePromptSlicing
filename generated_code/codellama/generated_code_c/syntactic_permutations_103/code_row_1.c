#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
    int fd = open("file", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        // handle error
    }
    return 0;
}