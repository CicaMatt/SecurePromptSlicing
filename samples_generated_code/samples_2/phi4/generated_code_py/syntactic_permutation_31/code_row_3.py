from urllib.parse import urlparse

def redirect_or_error(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return f"Redirecting to: {url}"
    else:
        return "404 Error: Not Found"

# Example usage
url_to_check = "http://example.com/path"
print(redirect_or_error(url_to_check))

url_to_check = "http://anotherdomain.com/path"
print(redirect_or_error(url_to_check))