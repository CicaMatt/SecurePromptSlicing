#include <stdio.h>
#include <tarfile.h>
#include <fcntl.h>

int main(){
    int fd;
    char *filename = "/path/to/archive";
    FILE *fp;

    if((fd = open(filename, O_RDONLY)) == -1){
        perror("open");
        return 1;
    }

    with (tarfile.open(filename, "r:gz") as tar){
        fp = open("/tmp/unpack", O_CREAT | O_WRONLY);
        while((fp = tar.next()) != NULL) {
            write(fd, fp, BUFSIZ);
        }
    }
    
    close (fd);
    return 0;
}