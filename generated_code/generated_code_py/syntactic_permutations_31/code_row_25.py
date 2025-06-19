import urllib.parse as ulp
def redirect_url(url):
    parsed_url = ulp.urlparse(url)
    netloc = parsed_url.netloc
    if netloc == 'example.com':
        return url
    else:
        raise ValueError("404 error")

### Test Cases:
    input: redirect_url('https://www.example.com')
    output: 'https://www.example.com'
    
    input: redirect_url('https://www.google.com')
