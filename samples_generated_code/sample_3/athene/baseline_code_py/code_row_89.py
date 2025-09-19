import re

REGEX = re.compile(r'^https?://example\.com/.*$')
DEFAULT_URL = 'http://default.com/'

def get_redirect_url(target_url):
    if REGEX.match(target_url):
        return target_url
    return DEFAULT_URL