import re

pattern = r'https://example\.com/.*'
default_url = 'https://default.com/'
regex = re.compile(pattern)

def get_redirect_target(url):
    if regex.match(url):
        return url
    else:
        return default_url