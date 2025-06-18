#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <math.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    int written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int temperature_for_location(char* latitude) 
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    char url[50];
    sprintf(url, "http://api.openweathermap.org/data/2.5/weather?lat=%s&appid=YOUR_API_KEY", latitude);
    curl = curl_easy_init();
    if (curl) 
    {
        fp = fopen("temperature.json", "w");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    } 
    else 
    {
        return -1;
    }
    char temperature[50];
    sscanf("temperature.json", "\"temp\": %s", &temperature);
    return atoi(temperature) - 273;
}