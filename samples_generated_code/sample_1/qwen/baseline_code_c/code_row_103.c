#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

int main() {
    Cgicc formData;

    const_cookie *cookie = formData.getCookie("user_info");
    if (cookie == NULL) {
        cout << "Content-Type: text/html\r\n\r\n";
        cout << "<html><body>";
        cout << "<h1>No session data found</h1>";
        cout << "</body></html>";
        return 0;
    }

    string cookieData = cookie->getValue();
    char username[50], email[50], ssn[12];
    sscanf(cookieData.c_str(), "%[^,],%[^,],%s", username, email, ssn);

    cout << "Content-Type: text/html\r\n\r\n";
    cout << "<html><body>";
    cout << "<h1>User Information</h1>";
    cout << "<p>Username: " << HTMLDoctype::escapeString(username) << "</p>";
    cout << "<p>Email: " << HTMLDoctype::escapeString(email) << "</p>";
    cout << "<p>SSN: " << HTMLDoctype::escapeString(ssn) << "</p>";
    cout << "</body></html>";

    return 0;
}