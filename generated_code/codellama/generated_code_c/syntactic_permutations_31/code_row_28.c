#include <string>
    using namespace std;
    string redirect_url(string url) {
        // Import urlparse from an appropriate module
        import urllib.parse as up
        // Parse the URL and get the network location
        parsed_url = up.urlparse(url)
        domain = parsed_url.netloc
        if (domain == "example.com") {
            return "https://www.example.com"
        } else {
            return url
        }
    }