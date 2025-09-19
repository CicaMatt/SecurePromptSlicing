import re

DEFAULT_REDIRECT_URL = 'https://default-url.com'

target_url_pattern = re.compile(r'^https://example\.com/.*$')

def get_redirect_url(target_url):
    if target_url_pattern.match(target_url):
        return target_url
    return DEFAULT_REDIRECT_URL