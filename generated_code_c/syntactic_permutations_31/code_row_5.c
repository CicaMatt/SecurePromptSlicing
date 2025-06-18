#include "http/client.h"
#include "url/parse.h"

void redirect_url(string url) {
    ParsedUrl parsed_url = parse_url(url);
    if (parsed_url.domain == "example.com") {
        return redirect(url, 301);
    } else {
        return error(404, "Not Found");
    }
}