import urllib.parse as urlparse

def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    netloc = parsed_url.netloc
    if netloc == "example.com":
        return url
    else:
        return 404