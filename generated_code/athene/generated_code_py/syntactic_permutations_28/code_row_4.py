import re

default_url = 'http://default.com'
target_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(url):
    if target_pattern.match(url):
        return url
    else:
        return default_url

# Example usage
url = 'http://example.com/somepage'
redirect_url = get_redirect_url(url)
print(redirect_url)