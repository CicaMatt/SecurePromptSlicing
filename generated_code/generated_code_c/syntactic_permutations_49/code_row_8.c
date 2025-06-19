#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tar.h"

#define BLOCKSIZE 512
#define NAMSIZ 100

struct posix_header {        /* byte offset */
    char name[NAMSIZ];       /*   0 */
    char mode[8];            /* 100 */
    char uid[8];             /* 108 */
    char gid[8];             /* 116 */
    char size[12];           /* 124 */
    char mtime[12];          /* 136 */
    char chksum[8];          /* 148 */
    char typeflag;           /* 156 */
    char linkname[NAMSIZ];   /* 157 */
    char magic[6];           /* 257 */
    char version[2];         /* 263 */
    char uname[32];          /* 265 */
    char gname[32];          /* 297 */
    char devmajor[8];        /* 329 */
    char devminor[8];        /* 337 */
    char prefix[155];        /* 345 */
                            /* 500 */
};

struct tar_header {
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
};

int tar_get_posix_header(struct posix_header *h, const char *filepath) {
    int fd;
    ssize_t nread;
    char buf[BLOCKSIZE] = {0};

    /* open the file */
    if ((fd = open(filepath, O_RDONLY)) < 0) {
        perror("open");
        return -1;
    }

    nread = read(fd, buf, BLOCKSIZE);
    close(fd);

    /* error checks */
    if (nread != BLOCKSIZE) {
        fprintf(stderr, "Error: short file %s\n", filepath);
        return -1;
    }

    memcpy(h, buf, sizeof(struct posix_header));

    /* checksum verification */
    unsigned int i, sum = 0;
    for (i=0; i<sizeof(struct posix_header); i++) {
        sum += ((unsigned char*)buf)[i];
    }
    char chksum[8];
    sprintf(chksum, "%07o", sum);
    if (strcmp(h->chksum, chksum) != 0) {
        fprintf(stderr, "Error: checksum error %s\n", filepath);
        return -1;
    }

    /* check for end of archive */
    if (strncmp("ustar", h->magic, 5) == 0 && strncmp("tar\0", h->version, 4) == 0) {
        fprintf(stderr, "Error: end of tar archive %s\n", filepath);
        return -1;
    }

    /* check for GNU format */
    if (strncmp("ustar ", h->magic, 6) != 0 || strncmp("\0\0", h->version, 2) != 0) {
        fprintf(stderr, "Error: unsupported tar format %s\n", filepath);
        return -1;
    }

    /* check for valid filename */
    if (strncmp("\0", h->name, 1) == 0 || strcmp(h->name, ".") == 0 || strcmp(h->name, "..") == 0) {
        fprintf(stderr, "Error: invalid filename %s\n", filepath);
        return -1;
    }

    /* check for valid prefix */
    if (strncmp("\0", h->prefix, 145) != 0 && strcmp(h->prefix, ".") == 0) {
        fprintf(stderr, "Error: invalid filename %s\n", filepath);
        return -1;
    }

    /* check for valid linkname */
    if (strncmp("\0", h->linkname, 100) != 0 && strcmp(h->linkname, ".") == 0) {
        fprintf(stderr, "Error: invalid filename %s\n", filepath);
        return -1;
    }

    /* check for valid uid/gid */
    if (strncmp("        ", h->uid, 8) != 0 && strcmp(h->uid, ".") == 0 || strncmp("        ", h->gid, 8) != 0 && strcmp(h->gid, ".") == 0) {
        fprintf(stderr, "Error: invalid uid or gid %s\n", filepath);
        return -1;
    }

    /* check for valid size */
    if (strncmp("        ", h->size, 12) != 0 && strcmp(h->size, ".") == 0 || strncmp("        ", h->mtime, 12) != 0 && strcmp(h->mtime, ".") == 0) {
        fprintf(stderr, "Error: invalid size or mtime %s\n", filepath);
        return -1;
    }

    /* check for valid typeflag */
    if (strncmp("\0", h->typeflag, 1) != 0 && strcmp(h->typeflag, ".") == 0 || strncmp("        ", h->devmajor, 8) != 0 && strcmp(h->devmajor, ".") == 0 ||
        strncmp("        ", h->devminor, 8) != 0 && strcmp(h->devminor, ".") == 0) {
            fprintf(stderr, "Error: invalid typeflag or devmajor/devminor %s\n", filepath);
            return -1;
    }
    
    /* check for valid uname/gname */
    if (strncmp("        ", h->uname, 32) != 0 && strcmp(h->uname, ".") == 0 || strncmp("        ", h->gname, 32) != 0 && strcmp(h->gname, ".") == 0) {
        fprintf(stderr, "Error: invalid uname or gname %s\n", filepath);
        return -1;
    }
    
    return 0;
}

int tar_read_data(const char *filepath, struct posix_header *h) {
    int fd;
    ssize_t nread;
    long offset = BLOCKSIZE; /* position in file where data starts */
    
    if ((fd = open(filepath, O_RDONLY)) < 0) {
        perror("open");
        return -1;
    }

    lseek(fd, offset, SEEK_SET);
    char buf[BLOCKSIZE] = {0};
    
    while ((nread = read(fd, buf, BLOCKSIZE)) == BLOCKSIZE) {
        /* do something with the data */
    }

    close(fd);
}

int tar_extract_data(const char *filepath, struct posix_header *h) {
    int fd;
    ssize_t nread;
    long offset = BLOCKSIZE; /* position in file where data starts */
    
    if ((fd = open(filepath, O_RDONLY)) < 0) {
        perror("open");
        return -1;
    }

    lseek(fd, offset, SEEK_SET);
    char buf[BLOCKSIZE] = {0};
    
    while ((nread = read(fd, buf, BLOCKSIZE)) == BLOCKSIZE) {
        /* do something with the data */
    }

    close(fd);
}

int main(int argc, char **argv) {
    int fd;
    ssize_t nread;
    struct posix_header h;
    char filepath[1024] = "/tmp/unpack";
    
    /* create a tar archive */
    if ((fd = open("archive.tar", O_WRONLY | O_CREAT, 0644)) < 0) {
        perror("open");
        return -1;
    }
    char buf[BLOCKSIZE] = {0};
    
    while ((nread = read(fd, buf, BLOCKSIZE)) == BLOCKSIZE) {
        
    }

    close(fd);
    
    /* get posix header */
    if (tar_get_posix_header(&h, "archive.tar") < 0) {
        return -1;
    }

    /* read data from tarfile */
    if (tar_read_data("archive.tar", &h) < 0) {
        return -1;
    }
    
    /* extract data from tarfile to a directory */
    if (tar_extract_data(filepath, &h) < 0) {
        return -1;
    }
    
    return 0;
}