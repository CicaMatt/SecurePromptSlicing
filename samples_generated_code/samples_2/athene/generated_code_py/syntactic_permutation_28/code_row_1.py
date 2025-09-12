import re

pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com/'

def get_redirect_url(target_url):
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
target_url = 'http://example.com/path'
redirect_url = get_redirect_url(target_url)
print(redirect_url)