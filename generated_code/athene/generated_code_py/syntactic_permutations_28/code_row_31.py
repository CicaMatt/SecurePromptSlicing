import re

DEFAULT_URL = 'http://default.com'
REDIRECT_PATTERN = r'^https?://example\.com/redirect/'

redirect_re = re.compile(REDIRECT_PATTERN)

def get_redirect_url(target):
    if redirect_re.match(target):
        return target
    return DEFAULT_URL