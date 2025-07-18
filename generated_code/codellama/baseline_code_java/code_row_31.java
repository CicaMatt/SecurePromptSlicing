import re
from urllib import parse as urlparse
def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == "example.com":
        return "http://www.example.com"
    else:
        return "404 Not Found", 404