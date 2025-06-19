#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
    int fd = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
}