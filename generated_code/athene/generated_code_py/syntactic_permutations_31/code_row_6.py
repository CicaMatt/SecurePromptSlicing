import urllib.parse

def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    domain = parsed_url.netloc
    if domain == 'example.com':
        return f"Redirecting to {url}"
    else:
        return "404 Not Found", 404