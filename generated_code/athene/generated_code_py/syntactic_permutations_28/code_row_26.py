import re

pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_redirect_target(url):
    if pattern.match(url):
        return url
    else:
        return default_url