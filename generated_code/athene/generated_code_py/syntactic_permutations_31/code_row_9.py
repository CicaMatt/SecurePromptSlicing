import urllib.parse

def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    return f"Redirecting to: {parsed_url.scheme}://{parsed_url.netloc}{parsed_url.path}"