#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <string.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <zlib.h>
    #include <tar.h>
    
    int main(void) {
        char *file_name = "test.txt";
        char *archive_file = "/tmp/unpack/test.tar.gz";
    
        // Unzip tar archive
        struct tar_info *ti = NULL;
        ti->archive = archive_file;
        ti->compressed = 1;
        ti->extract = "/tmp/unpack";
        int ret = tar_extract(ti);
        if (ret != 0) {
            printf("Error extracting %s\n", archive_file);
            return -1;
        }
    
        // Open and read file
        char *fname = "/tmp/unpack/test.txt";
        int fd = open(fname, O_RDONLY);
        if (fd < 0) {
            printf("Error opening %s\n", fname);
            return -1;
        }
    
        char *buf = malloc(BUFSIZ + 1);
        size_t nread;
        while ((nread = read(fd, buf, BUFSIZ)) > 0) {
            buf[nread] = '\0';
            printf("%s", buf);
        }
    
        free(buf);
        close(fd);
    
        return 0;
    }