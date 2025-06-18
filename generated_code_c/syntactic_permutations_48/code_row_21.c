#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/CgiDefs.h>
#include <iostream>
using namespace std;
using cgicc::Cgicc;
using cgicc::HTTPResponse;
int main(){
    Cgicc formData; // Creating Form Data
    const char* filename = formData("file").c_str(); // Get Filename
    int fd = open(filename, O_RDONLY); // Open File in Read-Only Mode
    if (fd == -1) { // Check for Errors
        cerr << "File Not Found!" << endl;
        exit(1);
    }
    struct stat fileStat; // Create Structure to Store File Statistics
    fstat(fd, &fileStat); // Get File Statistics
    char *buffer = (char*)malloc(fileStat.st_size + 1); // Allocate Memory for File Contents
    read(fd, buffer, fileStat.st_size); // Read File Contents into Buffer
    close(fd); // Close File
    HTTPResponse response; // Create Response Object
    response.setContentType("image/jpeg"); // Set Content-Type Header
    response.setContentLength(fileStat.st_size); // Set Content-Length Header
    response.setCookie("name", "value"); // Set Cookie
    response.setStatus(true); // Set Status
    cout << response.render() << buffer; // Render Response with File Contents
    return 0;
}