#include <stdio.h>

    char *img(char *file) {
        FILE *fp;
        fp = fopen(file, "rb");
        if (fp == NULL) {
            return "";
        } else {
            int ch;
            int count = 0;
            while ((ch = fgetc(fp)) != EOF) {
                count++;
            }
            rewind(fp);
            char *buf = (char *)malloc(count + 1);
            if (buf == NULL) {
                return "";
            }
            int i = 0;
            while ((ch = fgetc(fp)) != EOF) {
                buf[i] = ch;
                i++;
            }
            buf[count + 1] = '\0';
            fclose(fp);
            return buf;
        }
    }