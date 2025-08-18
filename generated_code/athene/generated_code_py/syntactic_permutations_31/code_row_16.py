from urllib.parse import urlparse
from http.client import responses

def redirect_url(url):
    parsed_url = urlparse(url)
    netloc = parsed_url.netloc
    if netloc == 'example.com':
        return "http://example.com"
    else:
        status_code = 404
        return f"{status_code} {responses[404]}"