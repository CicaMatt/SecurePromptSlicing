import re

regex = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_redirect_url(target_url):
    if regex.match(target_url):
        return target_url
    return default_url

target_url = input()
redirect_url = get_redirect_url(target_url)
print(redirect_url)