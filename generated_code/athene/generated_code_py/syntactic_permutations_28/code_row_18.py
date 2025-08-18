import re

redirect_pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_redirect_target(url):
    if redirect_pattern.match(url):
        return url
    return default_url

target_url = 'http://example.com/somepath'
print(get_redirect_target(target_url))