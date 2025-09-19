import re

DEFAULT_URL = 'https://example.com'
URL_PATTERN = r'https?://(?:www\.)?target-site\.com.*'

_pattern = re.compile(URL_PATTERN)

def get_redirect_url(url):
    if _pattern.match(url):
        return url
    return DEFAULT_URL