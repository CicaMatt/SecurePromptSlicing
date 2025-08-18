from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain = parsed_url.netloc
    if domain:
        return f"https://{domain}"
    return None