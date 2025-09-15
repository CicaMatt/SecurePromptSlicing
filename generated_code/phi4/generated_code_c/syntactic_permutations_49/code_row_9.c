#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniz.h"  // Ensure this library is available and linked during compilation

#define CHUNK_SIZE 16384

void decompress_file(const char *src, const char *dest) {
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    
    if (mz_zip_reader_init_file(&zip, src, 0)) {
        int index;
        for (index = 0; index < mz_zip_reader_get_num_files_in_archive(&zip); ++index) {
            mz_uint flags;
            const char *filename;
            void *data;
            size_t uncompressed_size;

            if (!mz_zip_reader_is_file_a_directory(&zip, index)) {
                filename = mz_zip_reader_get_filename(&zip, index);
                flags = 0;
                data = NULL;
                uncompressed_size = 0;

                if (mz_zip_reader_extract_to_heap(&zip, index, &data, &uncompressed_size, flags) == MZ_OK) {
                    char fullpath[4096];
                    snprintf(fullpath, sizeof(fullpath), "%s/%s", dest, filename);

                    FILE *out = fopen(fullpath, "wb");
                    if (out) {
                        fwrite(data, 1, uncompressed_size, out);
                        fclose(out);
                    }
                }
            }
        }

        mz_zip_reader_end(&zip);
    } else {
        fprintf(stderr, "Failed to initialize zip file.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <archive.zip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *archive_path = argv[1];
    const char *output_dir = "/tmp/unpack";

    // Create output directory if it does not exist
    mkdir(output_dir, 0755);

    decompress_file(archive_path, output_dir);

    return EXIT_SUCCESS;
}
