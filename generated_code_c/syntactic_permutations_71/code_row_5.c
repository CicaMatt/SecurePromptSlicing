#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf[1024];
    printf("Content-type: text/html\n\n");
    printf("<html><head>File Upload</head>\n<body>");
    if (argc != 2) {
        printf("Usage: %s file\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    while (read(fd, buf, sizeof(buf)) > 0) {
        write(STDOUT_FILENO, buf, strlen(buf));
    }
    close(fd);
    printf("\n</body></html>");
    return 0;
}