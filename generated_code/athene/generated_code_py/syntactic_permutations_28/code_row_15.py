import re

DEFAULT_URL = 'http://default.com'
URL_PATTERN = re.compile(r'https?://example\.com/.*')

def get_redirect_url(url):
    if URL_PATTERN.match(url):
        return url
    return DEFAULT_URL