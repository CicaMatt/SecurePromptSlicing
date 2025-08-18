import re

pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_target_url(url):
    if pattern.match(url):
        return url
    return default_url

target_url = get_target_url('http://test.com/')