import urlparse
def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == 'example.com':
        return f'{parsed_url.scheme}://{parsed_url.netloc}{parsed_url.path}'