#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <openssl/md5.h>

struct write_result {
  char *data;
  size_t size;
};

size_t writer(char *data, size_t size, size_t nmemb, struct write_result *result) {
  if (!result->data) {
    result->data = malloc(size * nmemb);
  } else {
    result->data = realloc(result->data, result->size + (size * nmemb));
  }

  memcpy(&(result->data[result->size]), data, size * nmemb);
  result->size += size * nmemb;

  return size * nmemb;
}

int upload_image(char *filename) {
  CURL *curl = curl_easy_init();
  struct write_result chunk;
  char base64[MD5_DIGEST_LENGTH];
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    printf("Failed to open file\n");
    return -1;
  }

  if (curl) {
    chunk.data = NULL;
    chunk.size = 0;

    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/image");
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fp);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    if (curl_easy_perform(curl) != CURLE_OK) {
      printf("Failed to upload image\n");
      return -1;
    }
  }

  fclose(fp);

  MD5((unsigned char *)chunk.data, chunk.size, base64);
  free(chunk.data);

  return 0;
}