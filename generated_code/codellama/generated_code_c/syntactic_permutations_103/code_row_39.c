#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main(void)
{
    int fd;
    fd = open("myfile", O_CREAT|O_TRUNC|O_WRONLY, 0644);
}