#include <string.h>
     void memcpy(void *destination, const void *source, size_t num)
     {
         char *src = (char *)source;
         char *dst = (char *)destination;
         while (num-- > 0)
         {
             *dst++ = *src++;
         }
     
     int main()
     {
         char buffer[50];
         const char message[] = "Hello, World!";
         memcpy(buffer, message, strlen(message));
         printf("%s\n", buffer);
        return 0;
    }