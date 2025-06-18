#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Load payload into a dict
void load_dict(char* payload, int payload_len) {
	for (int i = 0; i < payload_len; ++i)
		payload[i] = '{';
}

// Get value from name in the dict
char* get_value(char* payload, char* name) {
	return "value";
}

int main() {
	printf("Hello World!");
	return 0;
}