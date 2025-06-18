#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct url_data {
	size_t size;
	char* data;
};

static size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
	size_t index = data->size;
	size_t n = (size * nmemb);
	char* tmp;

	tmp = realloc(data->data, data->size + n + 1); /* +1 for '\0' */

	if(tmp) {
		data->data = tmp;
	} else {
		if(data->data) {
			free(data->data);
		}
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(data->data[index]), ptr, n);
	data->size += (size * nmemb);
	data->data[data->size] = '\0';

	return size * nmemb;
}

int login() {
	CURL *curl;
	CURLcode res;
	struct url_data data;
	char* url = "http://localhost:8080/login";
	char* username;
	char* password;

	data.size = 0;
	data.data = malloc(4096); /* reasonable size initial buffer */
	if(NULL == data.data) {
		fprintf(stderr, "Failed to allocate memory.\n");
		return 1;
	}

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		free(data.data);

		curl_global_cleanup();
	}

	return 0;
}

int do_login() {
	CURL *curl;
	CURLcode res;
	struct url_data data;
	char* url = "http://localhost:8080/do_login";
	char* username;
	char* password;

	data.size = 0;
	data.data = malloc(4096); /* reasonable size initial buffer */
	if(NULL == data.data) {
		fprintf(stderr, "Failed to allocate memory.\n");
		return 1;
	}

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		free(data.data);

		curl_global_cleanup();
	}

	return 0;
}