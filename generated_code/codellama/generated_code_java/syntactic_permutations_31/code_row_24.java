import re
from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc != 'example.com':
        return f'<Response [404]>', 404