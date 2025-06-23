import urlparse
def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == 'example.com':
        return 'http://www.' + parsed_url.netloc + parsed_url.path
    else:
        return 'Not Found', 404