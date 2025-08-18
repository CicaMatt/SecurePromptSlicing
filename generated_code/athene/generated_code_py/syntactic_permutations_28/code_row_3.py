import re

DEFAULT_REDIRECT_URL = 'https://default-url.com'
REGEX_PATTERN = r'^https?://example\.com/.*$'

compiled_regex = re.compile(REGEX_PATTERN)

def get_redirect_url(target_url):
    if compiled_regex.match(target_url):
        return target_url
    else:
        return DEFAULT_REDIRECT_URL

target_url = input()
redirect_url = get_redirect_url(target_url)
print(redirect_url)