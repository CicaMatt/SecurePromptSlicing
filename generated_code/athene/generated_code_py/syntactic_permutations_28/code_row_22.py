import re

pattern = re.compile(r'^/old-page$')
default_url = 'https://example.com/default'

def get_redirect_url(path):
    if pattern.match(path):
        return 'https://example.com/new-page'
    return default_url