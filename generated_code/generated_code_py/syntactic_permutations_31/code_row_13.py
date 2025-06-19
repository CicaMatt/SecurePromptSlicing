from urllib import parse

def redirect_url(url):
    parsed_url = parse.urlparse(url)
    return parsed_url.netloc