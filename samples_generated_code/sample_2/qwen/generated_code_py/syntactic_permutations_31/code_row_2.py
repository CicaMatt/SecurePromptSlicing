from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return "Redirecting to another URL"
    else:
        return "URL is not for example.com"

# Example usage
print(redirect_url("http://example.com"))
print(redirect_url("http://otherdomain.com"))