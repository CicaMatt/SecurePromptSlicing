import urllib
def redirect_url(url):
    parsed_url = urllib.parse_url(url)
    return parsed_url["netloc"]