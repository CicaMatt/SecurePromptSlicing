import re
from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return f"https://{parsed_url.netloc}{parsed_url.path}"
    else:
        return None