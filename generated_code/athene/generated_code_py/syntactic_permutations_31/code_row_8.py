from urllib.parse import urlparse
from http import HTTPStatus

def redirect_url(url):
    parsed_url = urlparse(url)
    domain = parsed_url.netloc
    if domain == 'example.com':
        return f"Redirecting to {url}"
    else:
        return ({"error": "Not Found"}, HTTPStatus.NOT_FOUND)