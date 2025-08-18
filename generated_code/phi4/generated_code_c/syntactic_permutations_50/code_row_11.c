#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>

#define CHUNK 16384

int mkdir_p(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        int ret = mkdir(path, 0777);
        if (ret != 0 && errno != EEXIST)
            return ret;
    }
    return 0;
}

void extract(const char *zipname, const char *dest) {
    FILE *fp_zip = fopen(zipname, "rb");
    if (!fp_zip) {
        perror("Failed to open zip file");
        exit(EXIT_FAILURE);
    }

    unsigned have;
    z_stream strm = {0};
    int ret;

    char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK) {
        fprintf(stderr, "inflateInit failed: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    do {
        strm.avail_in = fread(strm.next_in = out, 1, CHUNK, fp_zip);
        if (ferror(fp_zip)) {
            (void)inflateEnd(&strm);
            fprintf(stderr, "Error reading zip file\n");
            exit(EXIT_FAILURE);
        }
        if (strm.avail_in == 0)
            break;
        strm.next_out = out;
        strm.avail_out = CHUNK;

        ret = inflate(&strm, Z_NO_FLUSH);
        switch (ret) {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR; /* and fall through */
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            (void)inflateEnd(&strm);
            fprintf(stderr, "inflate failed: %d\n", ret);
            exit(EXIT_FAILURE);
        }

        have = CHUNK - strm.avail_out;
        // Process decompressed data
        char buffer[CHUNK];
        int count;
        while ((count = fread(buffer, 1, CHUNK, fp_zip)) > 0) {
            fwrite(buffer, 1, count, stdout); // This should be replaced with actual extraction logic
        }

    } while (strm.avail_in != 0);

    /* clean up and close */
    inflateEnd(&strm);
    fclose(fp_zip);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <zipfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *zipname = argv[1];
    const char *dest = "/tmp/unpack";

    mkdir_p(dest);

    extract(zipname, dest);
    
    return EXIT_SUCCESS;
}