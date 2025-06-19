import urllib.parse
from http import HTTPStatus

def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    network_location = parsed_url.netloc
    if network_location == 'example.com':
        return 'Redirecting to example.com'
    else:
        return HTTPStatus.NOT_FOUND