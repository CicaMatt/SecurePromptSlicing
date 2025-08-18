#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <curl/curl.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather"

typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *) userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = '\0';

    return realsize;
}

int get_max_temperature(double lat, double lon, int year, int month, int day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperatures WHERE latitude = %f AND longitude = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", 
             lat, lon, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    
    int max_temp = row ? atoi(row[0]) : -9999;

    mysql_free_result(res);
    mysql_close(conn);

    return max_temp;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        char *request_url = "/api/temperature_for_location";
        curl_easy_setopt(curl, CURLOPT_URL, request_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Assume JSON parsing happens here and extracts the required parameters
            double latitude = 34.0522;
            double longitude = -118.2437;
            int year = 2023;
            int month = 10;
            int day = 1;
            const char *grib_file = "sample.grib";

            int max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file);
            printf("Max Temperature: %d\n", max_temp);
        }

        free(chunk.memory);

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}


Make sure to link against the MySQL and cURL libraries when compiling this program. For example:


gcc -o app main.c $(mysql_config --cflags --libs) -lcurl