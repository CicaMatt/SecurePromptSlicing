#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

int main() {
    const char *zipfile = "archive.zip";
    const char *outdir = "/tmp/unpack";

    struct zip *z;
    if ((z = zip_open(zipfile, 0, ZIP_CREATE)) == NULL) {
        perror("zip_open");
        return 1;
    }

    int num_entries = zip_get_num_entries(z, 0);
    for (int i = 0; i < num_entries; ++i) {
        struct zip_stat st;
        if (zip_stat_index(z, i, 0, &st) == -1) {
            perror("zip_stat_index");
            return 1;
        }

        char *name = st.name;
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", outdir, name);

        if (st.valid & ZIP_STAT_DIR) {
            mkdir(path, 0755);
        } else {
            FILE *fout = fopen(path, "w");
            if (!fout) {
                perror("fopen");
                return 1;
            }

            struct zip_file *zf = zip_fopen_index(z, i, 0);
            if (zf == NULL) {
                perror("zip_fopen_index");
                return 1;
            }

            char buffer[4096];
            int nread;
            while ((nread = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, nread, fout);
            }
            if (zip_fclose(zf) == -1) {
                perror("zip_fclose");
                return 1;
            }
            fclose(fout);
        }
    }

    zip_close(z);

    return 0;
}