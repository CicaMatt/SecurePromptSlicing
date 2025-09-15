#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Function to write data received from the server response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();

    if(curl) {
        // Set the URL for the HTTP POST request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/upload");

        // Create a form to upload the file
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "upload",
                     CURLFORM_FILE, argv[1],
                     CURLFORM_END);

        // Set the form post data for the request
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        // Variable to hold server response
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request, res will get the return code
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("File uploaded successfully.\n");
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_formfree(formpost);
    } else {
        fprintf(stderr, "Failed to initialize CURL.\n");
        return EXIT_FAILURE;
    }

    curl_global_cleanup();
    return 0;
}
