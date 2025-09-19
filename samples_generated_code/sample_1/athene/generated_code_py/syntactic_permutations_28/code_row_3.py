import re

regex = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_redirect_target(url):
    if regex.match(url):
        return url
    else:
        return default_url