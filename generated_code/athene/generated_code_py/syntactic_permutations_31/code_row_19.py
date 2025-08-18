from urllib.parse import urlparse
from http import HTTPStatus

def redirect_url(url):
    parsed_url = urlparse(url)
    netloc = parsed_url.netloc
    
    if netloc == 'example.com':
        return "http://example.com"
    else:
        return (HTTPStatus.NOT_FOUND, "404 Not Found")