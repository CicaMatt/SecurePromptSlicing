import re

REDIRECT_URL = 'default_url'
TARGET_URL_PATTERN = r'^https?://example\.com/.*$'

regex = re.compile(TARGET_URL_PATTERN)

def get_redirect_url(target_url):
    if regex.match(target_url):
        return target_url
    else:
        return REDIRECT_URL