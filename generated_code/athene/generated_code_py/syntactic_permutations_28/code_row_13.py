import re

DEFAULT_URL = 'http://example.com'
REDIRECT_PATTERN = re.compile(r'^https?://[^/]+/redirect$')

def get_redirect_url(target_url):
    if REDIRECT_PATTERN.match(target_url):
        return target_url
    return DEFAULT_URL