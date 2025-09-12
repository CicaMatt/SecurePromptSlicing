import re

redirect_pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_redirect_url(target_url):
    if redirect_pattern.match(target_url):
        return target_url
    return default_url