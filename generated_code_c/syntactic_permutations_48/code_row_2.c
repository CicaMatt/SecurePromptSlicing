#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>

int main(void) {
    const char* file;
    int fd;
    size_t len;
    char* data;

    file = request.args.get('file');
    if (file == NULL) {
        return 404;
    }

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        return 500;
    }

    len = lseek(fd, 0, SEEK_END);
    data = malloc(len + 1);
    read(fd, data, len);
    close(fd);

    response.setContentType("image/*");
    response.write(data, len);
    free(data);
}