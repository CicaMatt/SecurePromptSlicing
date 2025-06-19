#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd = open("myfile", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
}