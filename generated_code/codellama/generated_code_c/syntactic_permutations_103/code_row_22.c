#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    return 0;
}