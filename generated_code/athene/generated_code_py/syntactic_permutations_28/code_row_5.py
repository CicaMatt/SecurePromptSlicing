import re

pattern = re.compile(r'^https://example\.com/path')
default_url = 'https://default.com/'

def get_redirect_target(url):
    if pattern.match(url):
        return url
    return default_url

redirect_url = get_redirect_target('https://example.com/path')  # Example usage
print(redirect_url)