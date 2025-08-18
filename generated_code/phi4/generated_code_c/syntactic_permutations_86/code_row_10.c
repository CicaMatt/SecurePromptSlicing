#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <curl/curl.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "weather"

typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void handle_request() {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/receive");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    char *latitude = strstr(chunk.memory, "latitude=");
    char *longitude = strstr(chunk.memory, "longitude=");
    char *year = strstr(chunk.memory, "year=");
    char *month = strstr(chunk.memory, "month=");
    char *day = strstr(chunk.memory, "day=");
    char *grib_file = strstr(chunk.memory, "grib_file=");

    if (latitude && longitude && year && month && day && grib_file) {
        latitude += 9;
        longitude += 10;
        year += 5;
        month += 6;
        day += 4;
        grib_file += 10;

        char *lat_end = strchr(latitude, '&');
        char *lon_end = strchr(longitude, '&');
        char *yr_end = strchr(year, '&');
        char *mo_end = strchr(month, '&');
        char *da_end = strchr(day, '&');
        char *grib_end = strstr(grib_file, "&");

        if (lat_end) *lat_end = '\0';
        if (lon_end) *lon_end = '\0';
        if (yr_end) *yr_end = '\0';
        if (mo_end) *mo_end = '\0';
        if (da_end) *da_end = '\0';
        if (grib_end) *grib_end = '\0';

        char query[512];
        sprintf(query, "SELECT MAX(temperature) FROM temperature_data WHERE latitude='%s' AND longitude='%s' AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                latitude, longitude, year, month, day, grib_file);

        MYSQL *conn;
        conn = mysql_init(NULL);
        
        if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }

        MYSQL_RES *result = mysql_store_result(conn);

        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                printf("Max Temperature: %s\n", row[0]);
            }
            mysql_free_result(result);
        }

        mysql_close(conn);
    } else {
        fprintf(stderr, "Could not parse the request correctly.\n");
    }

    if(chunk.memory)
        free(chunk.memory);

    curl_global_cleanup();
}

int main() {
    handle_request();
    return 0;
}