import re

DEFAULT_URL = 'http://default.com'
REDIRECT_URL = 'http://redirect.com'

url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url):
    if url_pattern.match(target_url):
        return REDIRECT_URL
    else:
        return DEFAULT_URL