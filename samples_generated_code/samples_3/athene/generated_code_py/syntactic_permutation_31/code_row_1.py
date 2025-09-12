from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain = parsed_url.netloc
    if domain:
        return f"Redirecting to: {url}"
    else:
        return "Error 404: Domain not found"