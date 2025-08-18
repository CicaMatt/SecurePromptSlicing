import re

DEFAULT_URL = 'https://example.com/default'
REDIRECT_PATTERN = re.compile(r'https://example\.com/redirect-\d+')

def get_redirect_url(target_url):
    if REDIRECT_PATTERN.match(target_url):
        return target_url
    return DEFAULT_URL