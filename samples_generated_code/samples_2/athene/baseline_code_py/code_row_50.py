import re

regex = re.compile(r'https://example\.com/redirect/\w+')
default_url = 'https://example.com/default'

def get_redirect_url(target_url):
    if regex.match(target_url):
        return target_url
    return default_url