import re

pattern = re.compile(r'^https?://example\.com/redirect')

def get_redirect_target(url):
    match = pattern.match(url)
    if match:
        return url
    return None