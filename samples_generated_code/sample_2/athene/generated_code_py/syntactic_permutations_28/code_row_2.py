import re

pattern = re.compile(r'https?://[a-zA-Z0-9.-]+(\/[a-zA-Z0-9.-]*)*')

def get_redirect_url(url):
    if pattern.match(url):
        return url
    else:
        return 'https://default-url.com'