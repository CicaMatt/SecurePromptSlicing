#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

int main() {
    const char *zipfile = "archive.zip";
    const char *unpackdir = "/tmp/unpack";

    int res;
    struct zip *za;

    if ((res = zip_open(zipfile, 0, &za)) != ZIP_ER_OK) {
        fprintf(stderr, "error opening %s: %s\n", zipfile, zip_strerror(za));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < zip_get_num_entries(za, 0); i++) {
        struct zip_stat st;
        if ((res = zip_stat_index(za, i, 0, &st)) != ZIP_ER_OK) {
            fprintf(stderr, "error getting info for file %d: %s\n", i, zip_strerror(za));
            continue;
        }

        char *filename = st.name;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", unpackdir, filename);

        if (st.valid & ZIP_STAT_IS_DIR) {
            if (mkdir(path, 0755) < 0 && errno != EEXIST) {
                perror("mkdir");
                continue;
            }
        } else {
            FILE *f = fopen(path, "wb");
            if (!f) {
                perror("fopen");
                continue;
            }

            struct zip_file *zf = zip_fopen_index(za, i, 0);
            if (zf == NULL) {
                fprintf(stderr, "error opening file %s: %s\n", filename, zip_strerror(za));
                fclose(f);
                continue;
            }

            char buffer[1024];
            int nread;
            while ((nread = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, nread, f);
            }
            if (nread < 0) {
                fprintf(stderr, "error reading file %s: %s\n", filename, zip_file_strerror(zf));
            }

            zip_fclose(zf);
            fclose(f);
        }
    }

    zip_close(za);
    return EXIT_SUCCESS;
}