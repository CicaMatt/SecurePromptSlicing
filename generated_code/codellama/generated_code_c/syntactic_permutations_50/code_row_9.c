#include<stdio.h>
    #include<stdlib.h>
    #include <archive.h>
    #include <archive_entry.h>

    int main()
    {
        struct archive *a;
        struct archive_entry *entry;
        int r;

        a = archive_read_new();
        archive_read_support_format_all(a);
        archive_read_support_filter_all(a);
        archive_read_open_filename(a, "archive.zip", 10240);

        while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
        {
            const char *name = archive_entry_pathname(entry);
            printf("%s\n", name);
            archive_read_data_skip(a);
        }

        r = archive_read_free(a);
    }