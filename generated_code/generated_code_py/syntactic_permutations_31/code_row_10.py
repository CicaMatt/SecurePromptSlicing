import urllib.parse as up
def redirect_url(url):
    p = up.urlparse(url)
    return f'{p.scheme}://{p.netloc}'