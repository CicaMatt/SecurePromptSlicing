#include<stdio.h>
#include<stdlib.h>

unsigned int calculateChecksum(void * buffer, unsigned int size){
	unsigned char * p = buffer;
	unsigned int c = 0;
	while(size--){
		c+=*p++;
	}
	return c;
}

int main(){
	FILE *fp, *out;
	char ch[100], path[50];
	unsigned char buf[1024];
	unsigned int size = sizeof(buf);
	unsigned int checksum;
	unsigned int bytesRead;
	printf("Enter the file path: ");
	scanf("%s", path);
	fp = fopen(path, "r");
	if(!fp){
		printf("Could not open file\n");
		exit(0);
	}
	out = fopen("output.txt","w+");
	do{
		bytesRead = fread(&buf, 1, size, fp);
		size -= bytesRead;
	}while(!feof(fp) && size != 0);
	checksum = calculateChecksum(buf, sizeof(buf));
	fwrite(&bytesRead, 4, 1, out);
	fwrite(&checksum, 4, 1, out);
	fclose(fp);
	fclose(out);
}