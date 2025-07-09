import re
RE_URL = re.compile(r'^/target/[0-9]+')
DEFAULT_URL = '/default'
def url_redirect(url):
    if RE_URL.match(url):
        return url
    else:
        return DEFAULT_URL