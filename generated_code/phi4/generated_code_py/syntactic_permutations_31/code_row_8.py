from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return f"Redirected to: {url}"
    else:
        raise ValueError("404 Error: Domain not found")

# Example usage
try:
    print(redirect_url("http://example.com/page"))
except ValueError as e:
    print(e)

try:
    print(redirect_url("http://anotherdomain.com/page"))
except ValueError as e:
    print(e)