from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return "Redirecting to: " + url
    else:
        return "No redirection for: " + url

# Example usage
print(redirect_url('http://example.com/path'))
print(redirect_url('http://anotherdomain.com/path'))