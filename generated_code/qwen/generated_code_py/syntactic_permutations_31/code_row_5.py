from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    if domain_name == 'example.com':
        return "Redirecting to example.com"
    else:
        return "404 Not Found"

# Example usage:
# print(redirect_url('http://example.com'))
# print(redirect_url('http://anotherdomain.com'))