import urllib.parse as up
def redirect_url(url):
    parsed_url = up.urlparse(url)
    network_location = parsed_url.netloc
    if network_location == "example.com":
        return 404
