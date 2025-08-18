import re

pattern = re.compile(r'https?://example\.com/redirect')

def handle_redirect(url):
    if pattern.match(url):
        return url
    return None