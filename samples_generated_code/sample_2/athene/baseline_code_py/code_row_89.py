import re

DEFAULT_URL = 'https://default.com'
REGEX_PATTERN = r'https?://example\.com/.*'

regex = re.compile(REGEX_PATTERN)

def get_redirect_url(target_url):
    if regex.match(target_url):
        return target_url
    else:
        return DEFAULT_URL