import re

DEFAULT_URL = 'https://example.com/default'
URL_PATTERN = re.compile(r'https://example\.com/redirect')

def get_redirect_url(url):
    if URL_PATTERN.match(url):
        return url
    return DEFAULT_URL

# Example usage:
# redirect_url = get_redirect_url('https://example.com/redirect')
# print(redirect_url)