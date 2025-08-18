import re

DEFAULT_URL = 'https://example.com/default'
REDIRECT_PATTERN = r'^https://example\.com/redirect-target$'

pattern = re.compile(REDIRECT_PATTERN)

def get_redirect_url(target_url):
    if pattern.match(target_url):
        return target_url
    return DEFAULT_URL

target_url = 'https://example.com/redirect-target'
print(get_redirect_url(target_url))