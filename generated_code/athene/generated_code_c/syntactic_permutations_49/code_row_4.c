#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <unistd.h>

void untar(const char *path, const char *dest) {
    FILE *fp;
    struct tar_header th;
    int n;

    if (chdir(dest) == -1) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    fp = fopen(path, "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (fread(&th, 1, sizeof(th), fp) != sizeof(th)) {
            break;
        }

        if (strcmp(th.name, "") == 0) {
            continue;
        }

        if (mkdir(th.name, 0755) == -1 && errno != EEXIST) {
            perror("mkdir");
            exit(EXIT_FAILURE);
        }

        if ((th.typeflag == REGULAR) && (n = atoi(th.size))) {
            FILE *ofp;

            ofp = fopen(th.name, "w");
            if (!ofp) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            while (n > 0) {
                int chunk;
                char buf[512];

                chunk = fread(buf, 1, n < 512 ? n : 512, fp);
                if (fwrite(buf, 1, chunk, ofp) != chunk) {
                    perror("fwrite");
                    exit(EXIT_FAILURE);
                }
                n -= chunk;
            }

            fclose(ofp);
        } else {
            fseek(fp, ((512 - atoi(th.size)) % 512), SEEK_CUR);
        }

        if (fseek(fp, 511 - ftell(fp) % 512 + 1, SEEK_CUR) != 0) {
            perror("fseek");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    const char *tarfile = "archive.tar";
    const char *dest_dir = "/tmp/unpack";

    if (mkdir(dest_dir, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    untar(tarfile, dest_dir);

    return 0;
}