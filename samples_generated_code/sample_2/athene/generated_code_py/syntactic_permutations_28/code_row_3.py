import re

DEFAULT_URL = 'https://default.com'

pattern = re.compile(r'https?://example\.com/.*')

def get_redirect_url(target_url):
    if pattern.match(target_url):
        return target_url
    else:
        return DEFAULT_URL