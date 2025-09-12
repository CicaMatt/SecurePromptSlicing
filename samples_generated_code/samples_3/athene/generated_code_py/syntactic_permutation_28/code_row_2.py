import re

pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='http://default.com'):
    if pattern.match(target_url):
        return target_url
    return default_url