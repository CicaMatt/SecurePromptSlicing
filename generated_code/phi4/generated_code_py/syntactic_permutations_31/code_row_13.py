from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        return f"Redirecting to {url}"
    else:
        return "404 Not Found"

# Example usage
print(redirect_url("http://example.com/some/page"))
print(redirect_url("http://anotherdomain.com/some/page"))