#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <assert.h>

    #include "base64/base64.h"
    #include "curl/curl.h"
    #include "json/json.h"

    /* Struct for image data */
    typedef struct {
        char* image_data;
        size_t image_size;
    } image_data_t;

    /* Function to encode image using base64 */
    void encode_image(char* filename, char** encoded_string) {
        image_data_t image_data = {0};
        FILE *fp = fopen(filename, "rb");
        if (fp == NULL) {
            printf("Error opening file\n");
            exit(1);
        }

        /* Get the size of the file */
        fseek(fp, 0L, SEEK_END);
        image_data.image_size = ftell(fp);
        rewind(fp);

        /* Allocate memory for the image data */
        image_data.image_data = (char*)malloc((image_data.image_size + 1) * sizeof(char));
        assert(image_data.image_data != NULL);

        /* Read the file into a buffer */
        size_t result = fread(image_data.image_data, 1, image_data.image_size, fp);
        if (result != image_data.image_size) {
            printf("Error reading from file\n");
            exit(1);
        }

        /* Encode the image data using base64 */
        *encoded_string = base64_encode((unsigned char*)image_data.image_data, image_data.image_size);
        assert(*encoded_string != NULL);
    }

    /* Function to upload image using curl */
    void upload_image(char* filename) {
        CURL *curl;
        CURLcode res;
        struct curl_slist *headers = NULL;
        char* encoded_string = NULL;

        encode_image(filename, &encoded_string);

        /* Initiate the curl handler */
        curl = curl_easy_init();
        if (curl) {
            headers = curl_slist_append(headers, "Content-Type: application/json");
            char* json_data = malloc(1024);
            sprintf(json_data, "{\"image\": \"%s\"}", encoded_string);

            /* Set URL and other appropriate options */
            curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/upload");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

            /* Perform the request */
            res = curl_easy_perform(curl);

            free(json_data);
            free(encoded_string);
        }
    }