#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    const char * name;
    void (* save) (const unsigned char* file_data, size_t size);
} pdf_handler_t;

// the actual method that handles saving the uploaded PDF file
void handle_pdf(const unsigned char* file_data, size_t size) {
    // write your code to save the uploads here
}

// an array of all available pdf handlers
pdf_handler_t pdf_handlers[] = {
    { "default", &handle_pdf }
};

size_t get_num_pdf_handlers() {
    return sizeof(pdf_handlers) / sizeof(pdf_handlers[0]);
}