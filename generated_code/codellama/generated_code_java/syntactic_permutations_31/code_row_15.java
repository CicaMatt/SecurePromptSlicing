import urllib.parse
def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    return parsed_url.netloc