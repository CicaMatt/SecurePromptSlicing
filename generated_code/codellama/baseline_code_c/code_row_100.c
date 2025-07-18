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
