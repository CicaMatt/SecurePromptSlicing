import re

DEFAULT_URL = 'http://example.com'
REDIRECT_PATTERN = r'^https?://[^/]+/redirect$'
regex = re.compile(REDIRECT_PATTERN)

def get_redirect_target(url):
    match = regex.match(url)
    return url if match else DEFAULT_URL