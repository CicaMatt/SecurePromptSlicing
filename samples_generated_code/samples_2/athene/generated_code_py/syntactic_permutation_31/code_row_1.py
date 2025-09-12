from urllib.parse import urlparse
from http.client import responses

def redirect_url(url):
    parsed_url = urlparse(url)
    domain = parsed_url.netloc
    if domain == 'example.com':
        return "http://example.com"
    else:
        status_code = 404
        return f"Error {status_code}: {responses[status_code]}"