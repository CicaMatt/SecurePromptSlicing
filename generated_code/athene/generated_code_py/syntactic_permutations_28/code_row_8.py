import re

regex = re.compile(r'^https://example\.com/.*$')
default_url = 'https://default.example.com/'

def get_redirect_url(target_url):
    if regex.match(target_url):
        return target_url
    else:
        return default_url