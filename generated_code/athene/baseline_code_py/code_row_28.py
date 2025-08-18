import re

DEFAULT_URL = 'https://default.com'
REDIRECT_PATTERN = r'^https://example\.com/redirect/\d+$'
redirect_regex = re.compile(REDIRECT_PATTERN)

def get_redirect_url(target_url):
    if redirect_regex.match(target_url):
        return target_url
    return DEFAULT_URL