import urllib.parse

def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    domain = parsed_url.netloc
    if domain == 'example.com':
        return 'https://example.com'
    else:
        return url