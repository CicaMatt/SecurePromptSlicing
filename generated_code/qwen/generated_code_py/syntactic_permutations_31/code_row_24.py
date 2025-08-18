from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return domain_name
    else:
        return "404 Error"