from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    return f"{parsed_url.scheme}://{parsed_url.netloc}/redirect"