import re

pattern = re.compile(r'^/old-path/$')

def get_redirect_url(path):
    if pattern.match(path):
        return '/new-path/'
    return '/default-url/'