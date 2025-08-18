import re

DEFAULT_URL = 'https://example.com'
REDIRECT_PATTERN = r'https://specific\.com/.*'

redirect_re = re.compile(REDIRECT_PATTERN)

def get_redirect_url(target_url):
    if redirect_re.match(target_url):
        return target_url
    return DEFAULT_URL