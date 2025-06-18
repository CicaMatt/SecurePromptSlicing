#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int fd;
fd = open("file", O_CREAT|O_WRONLY|O_EXCL, 0644);