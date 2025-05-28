import urllib.parse as up
def redirect_url(url):
    parsed_url = up.urlparse(url)
    network_location = parsed_url.netloc
    if network_location == "example.com":
        return 404
### Explanation:
This code uses the urllib.parse module to parse a given URL and determine its domain name. If the domain name is not example.com, a 404 error is returned.