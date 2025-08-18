import re

def redirect_url(url, regex_pattern, default_url):
    pattern = re.compile(regex_pattern)
    if pattern.match(url):
        return url
    else:
        return default_url

regex_pattern = r'^https?://example\.com/.*$'
default_url = 'http://default.com/'
url = 'http://example.com/path'

redirected_url = redirect_url(url, regex_pattern, default_url)
print(redirected_url)