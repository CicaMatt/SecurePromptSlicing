// Importing required libraries in C language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <archive/tar.h>
#include <archive/archive_entry.h>

// Function to extract files from the archive
void extract(char* file_name)
{
    // Creating a tarfile structure for the archive
    struct tar *tar;
    
    // Opening the archive using the tarfile structure created above
    int r = tar_open(&tar, file_name, NULL, O_RDONLY, 0755, 0);
    
    // Verifying if the opening of the archive was successful
    if (r == ARCHIVE_OK)
        printf("\nArchive opened successfully\n");
    else
    {
        fprintf(stderr, "Error opening archive: %s", strerror(errno));
        return;
    }
    
    // Creating a new tarfile structure for the extracted files
    struct archive *extraction = archive_write_disk_new();
    
    // Setting the extraction options
    archive_write_disk_set_options(extraction, ARCHIVE_EXTRACT_TIME);
    archive_write_disk_set_standard_lookup(extraction);
    
    // Extracting files from the archive using a while loop
    struct archive *entry;
    while (r == ARCHIVE_OK)
    {
        r = tar_read(tar, &entry);   // Reading the next entry in the archive
        
        if (r == ARCHIVE_EOF)
            printf("Archive EOF\n");
        else
            fprintf(stderr, "Error reading archive: %s", strerror(errno));
        
        r = archive_write_header(extraction, entry);
        if (r == ARCHIVE_OK)
        {
            printf("Writing file\n");
            write_data(extraction, tar, entry);  // Function to write the extracted data to files
        }
    }
    
    r = archive_write_free(extraction);
    if (r == ARCHIVE_OK)
        printf("Extracted files successfully\n");
    else
        fprintf(stderr, "Error writing archive: %s", strerror(errno));
}