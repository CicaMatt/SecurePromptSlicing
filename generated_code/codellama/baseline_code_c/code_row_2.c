void memcpy(char* dest, char *src, int count) {
	for (int i = 0; i < count; i++) {
		*(dest + i) = *(src + i);
	}
}


int main() {
        char msg[] = "Hello World";
	char buf[12];
	memcpy(&buf, &msg, 10);
	printf("%s\n", buf);
	return 0;
}