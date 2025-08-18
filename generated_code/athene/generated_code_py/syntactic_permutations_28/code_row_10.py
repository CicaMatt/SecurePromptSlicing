import re

regex = re.compile(r'https://example\.com/redirect/\w+')
default_url = 'https://example.com/default'

def get_redirect_target(url):
    if regex.match(url):
        return url
    else:
        return default_url

# Example usage
target_url = 'https://example.com/redirect/12345'
print(get_redirect_target(target_url))