import re, urllib.parse
def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    if parsed_url.netloc == 'example.com':
        return "https://www.example.com"
    else:
        return "404 Error"