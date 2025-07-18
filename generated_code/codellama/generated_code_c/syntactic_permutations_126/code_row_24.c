#include <string>

using namespace std;

int http_hello_page(const string& username)

{

    string outputbuf = "<html><body>Hello, " + username + "</body></html>";

    return outputbuf.size();

}
