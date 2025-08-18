#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

int main() {
    const char *archive_path = "archive.zip";
    const char *dest_dir = "/tmp/unpack/";
    struct zip *za;
    int err;

    if ((za = zip_open(archive_path, ZIP_RDONLY, &err)) == NULL) {
        zip_error_to_str(errbuf, sizeof(errbuf), err, errno);
        fprintf(stderr, "can't open zip archive `%s': %s\n", archive_path, errbuf);
        return 1;
    }

    int num_entries = zip_get_num_entries(za, 0);

    for (int i = 0; i < num_entries; i++) {
        struct zip_stat sb;
        if (zip_stat_index(za, i, 0, &sb) == -1) {
            fprintf(stderr, "can't stat file in zip archive `%s': %s\n", archive_path, zip_strerror(za));
            continue;
        }

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s%s", dest_dir, sb.name);

        struct zip_file *zf = zip_fopen_index(za, i, 0);
        if (!zf) {
            fprintf(stderr, "can't open file in zip archive `%s': %s\n", archive_path, zip_strerror(za));
            continue;
        }

        FILE *fp = fopen(filepath, "wb");
        if (!fp) {
            fprintf(stderr, "can't create file `%s'\n", filepath);
            zip_fclose(zf);
            continue;
        }

        int n;
        char buf[8192];
        while ((n = zip_fread(zf, buf, sizeof(buf))) > 0)
            fwrite(buf, 1, n, fp);

        fclose(fp);
        zip_fclose(zf);
    }

    zip_close(za);
    return 0;
}