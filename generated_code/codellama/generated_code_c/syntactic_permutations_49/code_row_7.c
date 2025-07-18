#include <stdio.h>
int main(){
	FILE *tar_file=fopen("archive.tar", "r");
	if(tar_file==NULL) return 0;
	else{
		unpack(tar_file, "/tmp/unpack");
	}
	return 1;
}