#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CURL_STATICLIB
#endif

#include <curl/curl.h>

// Function to write data received from curl into a file
size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int upload_pdf(const char *filename) {
    CURL *curl;
    CURLcode res;

    // Initialize a libcurl handle
    curl = curl_easy_init();
    if (curl) {
        // Open file for writing
        FILE *fp = fopen("uploads/file.pdf", "wb");
        if (!fp) {
            fprintf(stderr, "Could not open file for writing\n");
            return -1;
        }

        // Set the URL to send data to
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/upload");

        // Specify that we want to upload a file
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Set the read function for libcurl's file transfer
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);

        // Set the size of the data being uploaded
        fseek(fp, 0, SEEK_END);
        long fsize = ftell(fp);
        rewind(fp);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);

        // Perform the file upload
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            fclose(fp);
            curl_easy_cleanup(curl);
            return -1;
        }

        // Clean up
        fclose(fp);
        curl_easy_cleanup(curl);

        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Error initializing libcurl\n");
        return -1;
    }
    return 0;
}

int main() {
    if (system("mkdir -p uploads") != 0 && _mkdir("uploads") != 0) {
        perror("Failed to create 'uploads' directory");
        return EXIT_FAILURE;
    }

    const char *filename = "path_to_your_pdf_file.pdf";
    upload_pdf(filename);

    return EXIT_SUCCESS;
}


Make sure to replace `"path_to_your_pdf_file.pdf"` with the actual path of your PDF file and have a web server running at `http://localhost:8080/upload` that can handle file uploads.