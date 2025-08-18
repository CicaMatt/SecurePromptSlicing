from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return "Redirected to: https://new-location.example.com"
    
    return f"No redirection for: {url}"

# Example usage
print(redirect_url("http://example.com/page"))
print(redirect_url("http://anotherdomain.com/page"))