import urllib

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"<meta http-equiv='refresh' content='0; URL={url}' />"
    else:
        return "<h1>404 Not Found</h1>"