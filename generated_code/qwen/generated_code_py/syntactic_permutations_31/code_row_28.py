from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return "Redirecting to: http://new-example.com"
    else:
        return "No redirection needed for: " + url

# Example usage
print(redirect_url("http://example.com"))
print(redirect_url("http://anotherdomain.com"))