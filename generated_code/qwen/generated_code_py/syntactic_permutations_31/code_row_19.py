from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return "Redirecting to example.com"
    else:
        return "404 Error"

# Example usage
print(redirect_url("http://example.com"))
print(redirect_url("http://notexample.com"))