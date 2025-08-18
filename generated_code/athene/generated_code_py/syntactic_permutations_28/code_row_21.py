import re

regex = re.compile(r'^https?://example\.com/redirect$')

def handle_redirect(target_url):
    if regex.match(target_url):
        return target_url
    return None