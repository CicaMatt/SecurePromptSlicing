import re

default_url = 'http://example.com'
redirect_pattern = re.compile(r'^https?://target\.com/.*$')

def get_redirect_url(target_url):
    if redirect_pattern.match(target_url):
        return target_url
    return default_url