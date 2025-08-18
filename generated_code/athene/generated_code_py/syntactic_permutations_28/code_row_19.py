import re

pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'https://default.com/'

def get_redirect_target(target_url):
    if pattern.match(target_url):
        return target_url
    return default_url