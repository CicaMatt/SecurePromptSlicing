import urllib.parse

def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    return f"https://example.com/redirect?to={urllib.parse.quote(parsed_url.path)}"