#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <zipfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *zipfile = argv[1];
    struct zip *archive;
    int err;

    if ((err = zip_open(zipfile, 0, &archive)) != ZIP_ER_OK) {
        fprintf(stderr, "Error opening %s: %s\n", zipfile, zip_err_str(err));
        return EXIT_FAILURE;
    }

    struct zip_file *zf;
    struct zip_stat st;
    char buffer[4096];
    int len;

    const char *unpack_dir = "/tmp/unpack";
    if (mkdir(unpack_dir, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        zip_close(archive);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < zip_get_num_files(archive); i++) {
        zip_stat_init(&st);
        if ((err = zip_stat_index(archive, i, 0, &st)) != ZIP_ER_OK) {
            fprintf(stderr, "Error getting file info: %s\n", zip_err_str(err));
            continue;
        }

        char *filename = st.name;
        char path[4096];
        snprintf(path, sizeof(path), "%s/%s", unpack_dir, filename);

        if (st.valid & ZIP_STAT_DIR) {
            mkdir(path, 0755);
            continue;
        }

        FILE *f = fopen(path, "wb");
        if (!f) {
            perror("fopen");
            zip_close(archive);
            return EXIT_FAILURE;
        }

        zf = zip_fopen_index(archive, i, 0);
        if (zf == NULL) {
            fprintf(stderr, "Error opening file in archive: %s\n", filename);
            fclose(f);
            continue;
        }

        while ((len = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, 1, len, f);
        }

        if (len < 0) {
            fprintf(stderr, "Error reading file: %s\n", filename);
        }

        zip_fclose(zf);
        fclose(f);
    }

    zip_close(archive);
    return EXIT_SUCCESS;
}