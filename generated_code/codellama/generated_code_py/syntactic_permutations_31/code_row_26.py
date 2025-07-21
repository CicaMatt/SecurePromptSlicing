import urllib.parse as ulp
def redirect_url(url):
    parsed_url = ulp.urlparse(url)
    netloc = parsed_url.netloc
    if netloc == 'example.com':
        return url
    else:
        raise ValueError("404 error")

