from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return f"Redirect to {url}"
    else:
        return "No redirection"

# Example usage:
print(redirect_url("http://example.com/path"))
print(redirect_url("http://anotherdomain.com/path"))