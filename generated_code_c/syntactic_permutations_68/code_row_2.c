#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>
    #include <mongoc.h>
    
    // Function to convert image to base64
    char* b64_encode(const void* buf, int len)
    {
        const unsigned char* in = (unsigned char*)buf;
        int i = 0;
        int j = 0;
        char *out = malloc(((len + 2) / 3) * 4);
        
        while (len--)
            out[i++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(in[j++] & 0xFC) >> 2];
        
        out[i++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(in[j] & 0xFC) >> 2];
        out[i++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(in[j++] & 0xFC) >> 2];
        
        while (i % 4)
            out[i++] = '=';
        
        return out;
    }
    
    // Function to insert image details into MongoDB database
    void upload_image(const char* img, const char *img_name)
    {
        mongoc_init();
        mongoc_client_t *client = mongoc_client_new("mongodb://localhost:27017/");
        
        mongoc_collection_t *collection = mongoc_client_get_collection(client, "db", "image_details");
        bson_t *doc = bson_new();
        BSON_APPEND_UTF8(doc, "img_name", img_name);
        BSON_APPEND_UTF8(doc, "base64_string", img);

        if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, NULL))
            printf("Insertion error\n");
        else 
            printf("Inserted successfully\n");
    }
    
    // Function to read the image file and convert it into base64 string
    void read_img(const char *filename)
    {
        FILE* fd = fopen(filename, "rb");  
        fseek(fd, 0L, SEEK_END);
        long int size = ftell(fd);
        rewind(fd);
        unsigned char* buffer = (unsigned char*)malloc(sizeof(char) * size);
        fread(buffer, sizeof(char), size, fd); 
        fclose(fd);
        
        upload_image(b64_encode(buffer, size), filename);
    }
    
    int main() {
        read_img("path/to/filename.jpg");
        return 0;
    }