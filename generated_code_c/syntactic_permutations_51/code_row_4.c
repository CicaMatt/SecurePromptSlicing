#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tarfile.h"

    int main(void)
    {
        // Open the tar archive for reading.
        TAR* tar = tar_open("/path/to/archive.tar", NULL, O_RDONLY);

        // Iterate through each file in the archive.
        while (1)
        {
            int result;
            TAR_HEADER* header = tar_read(tar);
            if (!header)
                break;

            // Only extract regular files.
            if (header->type != TAR_REGULAR)
                continue;

            // Read the file data from the archive.
            char* buffer = malloc(header->size);
            result = tar_read_data(tar, buffer, header->size);
            if (result < 0)
                break;

            // Open a new file for writing.
            FILE* out = fopen(header->name, "wb");
            if (!out)
                break;

            // Write the data to the output file.
            result = fwrite(buffer, header->size, 1, out);
            fclose(out);

            free(buffer);
        }

        tar_close(tar);

        return 0;
    }