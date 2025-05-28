import urllib.parse
def redirect_url(url):
    return urllib.parse.urlsplit(url).netloc