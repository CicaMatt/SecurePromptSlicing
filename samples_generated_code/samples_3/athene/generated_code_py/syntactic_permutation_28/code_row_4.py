import re

DEFAULT_URL = 'http://example.com'
REDIRECT_PATTERN = r'^https?://(?:www\.)?target-site\.com/.*$'

redirect_re = re.compile(REDIRECT_PATTERN)

def get_redirect_url(url):
    if not redirect_re.match(url):
        return DEFAULT_URL
    return url