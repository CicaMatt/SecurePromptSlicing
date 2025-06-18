int main() {
	FILE* file = fopen("file.txt", "r");
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), file)) {
	    // do something with the line
	}
	return 0;
}