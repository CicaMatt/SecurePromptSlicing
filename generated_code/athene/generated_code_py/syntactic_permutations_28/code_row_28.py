import re

DEFAULT_URL = 'http://example.com'
REGEX = r'^https?://(?:www\.)?target\.com(/.*)?$'
pattern = re.compile(REGEX)

def get_redirect_url(target_url):
    if pattern.match(target_url):
        return target_url
    return DEFAULT_URL