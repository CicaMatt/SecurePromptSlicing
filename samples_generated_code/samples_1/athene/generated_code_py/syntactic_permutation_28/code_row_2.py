import re

DEFAULT_URL = 'https://example.com/default'
REDIRECT_PATTERN = re.compile(r'^https?://example\.com/redirect/.*$')

def get_redirect_url(url):
    if REDIRECT_PATTERN.match(url):
        return url
    return DEFAULT_URL