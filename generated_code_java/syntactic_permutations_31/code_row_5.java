import urllib.parse
def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"<html><head><meta http-equiv=\"refresh\" content=\"0; url={parsed_url}\"/></head><body></body></html>"
    else:
        return "<h1>404 Not Found</h1>"