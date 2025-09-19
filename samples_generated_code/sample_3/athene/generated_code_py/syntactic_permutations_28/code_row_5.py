import re

DEFAULT_URL = 'https://example.com'
REDIRECT_PATTERN = r'^https?://.*\.com/$'
redirect_re = re.compile(REDIRECT_PATTERN)

def get_redirect_target(url):
    if redirect_re.match(url):
        return url
    return DEFAULT_URL