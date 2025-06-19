#include <string>
using namespace std;
int http_hello_page(const string& username)
{
    string outputbuf = "<html><body>Hello, " + username + "</body></html>";
    return outputbuf.size();
}


### Explanation:
The code imports the C++ string library and assigns the input parameter username to the local variable outputbuf as part of the response body. The function returns the size of the output buffer, which can be used to determine if any data was written and how much data was written.