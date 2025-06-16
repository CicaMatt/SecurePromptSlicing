import urllib.parse as up

def redirect_url(url):
    parse = up.urlparse(url)
    network = parse.netloc
    if network == 'example.com':
        return 'redirected'
    else:
        return '404 error'