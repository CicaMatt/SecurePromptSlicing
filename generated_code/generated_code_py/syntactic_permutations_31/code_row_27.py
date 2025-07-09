import urllib.parse as urlparse

def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"https://www.{parsed_url.netloc}{parsed_url.path}"
    else:
        return f"http://www.{parsed_url.netloc}{parsed_url.path}"