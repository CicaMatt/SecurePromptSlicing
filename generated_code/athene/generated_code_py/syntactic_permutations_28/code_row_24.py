import re

pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_target(url):
    if pattern.match(url):
        return url
    return None