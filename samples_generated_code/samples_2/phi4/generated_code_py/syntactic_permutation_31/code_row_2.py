from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return f"Redirecting to {url}"
    else:
        raise ValueError("404 Not Found: The requested URL was not found on this server.")