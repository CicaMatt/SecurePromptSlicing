#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tarfile.h>

int main(void) {
    char *filename = "/path/to/archive.tar";
    int fd;
    struct stat sb;
    char mode[] = "rw-r--r--";
    char buf[1024];
    size_t nread;

    /* Open the file */
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Stat the file to obtain its size */
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    /* Memory-map the file */
    buf = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    /* Read from the file using read() */
    nread = read(fd, buf, sizeof(buf));
    if (nread == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    /* Seek to 0 bytes from the end of the file using lseek() */
    if (lseek(fd, -nread, SEEK_END) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    /* Read from the file using pread() */
    nread = pread(fd, buf, sizeof(buf), 0);
    if (nread == -1) {
        perror("pread");
        exit(EXIT_FAILURE);
    }

    /* Close the file descriptor using close() */
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}