import urlparse
def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == 'example.com':
        return "https://www.example.com"
    else:
        return "Not Found", 404