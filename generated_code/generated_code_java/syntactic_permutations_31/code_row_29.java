import re
from urllib.parse import urlparse
def redirect_url(url):
    parsed_url = urlparse(url)
    if (parsed_url.netloc == 'example.com'):
        return url
    else:
        return None