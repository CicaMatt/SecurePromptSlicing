import re

pattern = re.compile(r'^https?://[a-zA-Z0-9.-]+(?:/[a-zA-Z0-9%_\-.]*)?$')
default_url = 'http://example.com'

def get_redirect_target(url):
    if pattern.match(url):
        return url
    else:
        return default_url