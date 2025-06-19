#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    // Function to encode file data to base64 encoded string
    char* base64_encode(const unsigned char* buffer, size_t length) {
        char* encoded_data = NULL;
        int encoded_data_length = 0;
        encoded_data_length = (((length - 1) / 3 + 1) << 2);
        encoded_data = (char*)malloc(encoded_data_length);

        if (!encoded_data)
            return NULL;

        int i, j;
        for (i = 0, j = 0; i < length - 2; i += 3) {
            encoded_data[j++] = ((buffer[i] & 0xFC) >> 2);
            encoded_data[j++] = (((buffer[i] & 0x03) << 4) + ((buffer[i + 1] & 0xF0) >> 4));
            encoded_data[j++] = (((buffer[i + 1] & 0x0F) << 2) + ((buffer[i + 2] & 0xC0) >> 6));
            encoded_data[j++] = (buffer[i + 2] & 0x3F);
        }

        if (i < length) {
            encoded_data[j++] = ((buffer[i] & 0xFC) >> 2);
            if (i == (length - 1)) {
                encoded_data[j++] = (((buffer[i] & 0x03) << 4) + ((buffer[i + 1] & 0xF0) >> 4));
                encoded_data[j++] = '=';
            }
            else {
                encoded_data[j++] = (((buffer[i] & 0x03) << 4) + ((buffer[i + 1] & 0xF0) >> 4));
                encoded_data[j++] = (((buffer[i + 1] & 0x0F) << 2) + ((buffer[i + 2] & 0xC0) >> 6));
            }
        }

        if (i < length - 1)
            encoded_data[j++] = '=';

        return encoded_data;
    }

    // Function to write base64 encoded string to file
    void write_base64(char* buffer) {
        int fd = open("encoded.txt", O_WRONLY | O_CREAT, 0644);
        if (fd < 0)
            return;

        size_t length = strlen(buffer);
        ssize_t written = write(fd, buffer, length);
        close(fd);
    }

    // Function to upload image and encode it using base64
    void upload_image() {
        int fd = open("image.jpg", O_RDONLY, 0644);
        if (fd < 0)
            return;

        struct stat file_info;
        fstat(fd, &file_info);
        unsigned char* buffer = (unsigned char*)malloc(file_info.st_size);
        read(fd, buffer, file_info.st_size);
        close(fd);

        char* encoded_data = base64_encode(buffer, file_info.st_size);
        if (!encoded_data)
            return;

        write_base64(encoded_data);
    }