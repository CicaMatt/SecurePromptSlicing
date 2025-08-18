import urllib.parse

def redirect_url(url):
    parsed_url = urllib.parse.urlparse(url)
    domain = parsed_url.netloc
    if domain.endswith('.com'):
        return 'https://www.example.com'
    else:
        return 'https://www.default-redirect.com'