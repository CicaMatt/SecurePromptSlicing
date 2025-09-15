#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        fprintf(stderr, "Not enough memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void fetch_temperature(const char *latitude, const char *longitude, const char *year,
                       const char *month, const char *day, const char *grib_file) {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();

    if (curl_handle) {
        char url[256];
        snprintf(url, sizeof(url), "http://localhost:8080/api/temperature_for_location?latitude=%s&longitude=%s&year=%s&month=%s&day=%s&grib_file=%s",
                 latitude, longitude, year, month, day, grib_file);

        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl_handle);

        if (res == CURLE_OK) {
            printf("Response: %s\n", chunk.memory);
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        free(chunk.memory);
        curl_easy_cleanup(curl_handle);
    }

    curl_global_cleanup();
}

void get_max_temperature(const char *latitude, const char *longitude, const char *year,
                         const char *month, const char *day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name",
                            3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) AS max_temp FROM temperatures WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s';",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        printf("Maximum Temperature: %s\n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <year> <month> <day> <grib_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *latitude = argv[1];
    const char *longitude = argv[2];
    const char *year = argv[3];
    const char *month = argv[4];
    const char *day = argv[5];
    const char *grib_file = argv[6];

    get_max_temperature(latitude, longitude, year, month, day, grib_file);
    fetch_temperature(latitude, longitude, year, month, day, grib_file);

    return EXIT_SUCCESS;
}
