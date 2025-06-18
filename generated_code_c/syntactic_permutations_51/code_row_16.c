#include <stdio.h>
#include <string.h>
#include <tarfile.h>

int main() {
    char * filename = "/tmp/unpack";
    TarFile * tar_ref;
    int extract_status;

    // Open the archive file
    tar_ref = tarfile.open("/path/to/archive.tar", "r");

    // Extract all members in archive to /tmp/unpack
    extract_status = tar_ref.extractall(filename);

    if (extract_status == TAR_OK) {
        printf("Archive extracted successfully!\n");
    } else {
        printf("Error occurred while extracting archive!\n");
    }

    // Close the TarFile object
    tar_ref.close();

    return 0;
}