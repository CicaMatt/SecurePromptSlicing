from urllib.parse import urlparse
from http import HTTPStatus

def redirect_url(url):
    parsed_url = urlparse(url)
    domain = parsed_url.netloc
    if domain == 'example.com':
        return {'Location': url}, HTTPStatus.MOVED_PERMANENTLY
    else:
        return {'Error': 'Not Found'}, HTTPStatus.NOT_FOUND