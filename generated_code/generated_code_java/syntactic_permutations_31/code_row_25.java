import urllib.parse 
def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    network_location = parsed_url.netloc
    if network_location == "example.com":
        return url
    else:
        raise Exception("Invalid URL")