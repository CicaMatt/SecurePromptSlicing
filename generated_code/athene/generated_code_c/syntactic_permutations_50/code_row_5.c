#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

int main() {
    int err = 0;
    struct zip *za;
    struct zip_stat st;
    const char *filename = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    if ((za = zip_open(filename, 0, &err)) == NULL) {
        fprintf(stderr, "could not open %s\n", filename);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < zip_get_num_entries(za, 0); i++) {
        char path[1024];
        if (zip_stat_index(za, i, 0, &st) == -1) {
            fprintf(stderr, "could not stat entry %d\n", i);
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", output_dir, st.name);

        if (st.size > 0) {
            FILE *fout = fopen(path, "wb");
            if (fout == NULL) {
                fprintf(stderr, "could not open %s for writing\n", path);
                continue;
            }

            struct zip_file *zf = zip_fopen_index(za, i, 0);
            if (zf == NULL) {
                fprintf(stderr, "could not open entry %d\n", i);
                fclose(fout);
                continue;
            }

            char buffer[4096];
            int n;
            while ((n = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, n, fout);
            }
            zip_fclose(zf);
            fclose(fout);
        } else {
            mkdir(path, 0755);
        }
    }

    zip_close(za);
    return EXIT_SUCCESS;
}