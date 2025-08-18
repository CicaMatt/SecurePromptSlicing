import re

_pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default-url.com/'

def get_redirect_target(url):
    match = _pattern.match(url)
    return match.group(0) if match else default_url