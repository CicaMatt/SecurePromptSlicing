#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

int main() {
    const char *zipfile = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    struct zip *za;
    if ((za = zip_open(zipfile, 0, ZIP_CREATE)) == NULL) {
        perror("zip_open");
        return EXIT_FAILURE;
    }

    int num_files = zip_get_num_entries(za, 0);
    for (int i = 0; i < num_files; i++) {
        struct zip_stat st;
        if (zip_stat_index(za, i, 0, &st) == -1) {
            perror("zip_stat_index");
            continue;
        }

        char *filename = strdup(st.name);
        if (filename == NULL) {
            perror("strdup");
            continue;
        }

        char fullpath[256];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", output_dir, filename);

        FILE *fout = fopen(fullpath, "w");
        if (fout == NULL) {
            free(filename);
            perror("fopen");
            continue;
        }

        struct zip_file *zf = zip_fopen_index(za, i, 0);
        if (zf == NULL) {
            fclose(fout);
            free(filename);
            perror("zip_fopen_index");
            continue;
        }

        char buffer[1024];
        int n;
        while ((n = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, 1, n, fout);
        }

        fclose(fout);
        zip_fclose(zf);
        free(filename);
    }

    if (zip_close(za) == -1) {
        perror("zip_close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}