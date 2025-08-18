from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        return f"Redirected to {url}"
    
    raise Exception("404 Not Found")

# Example usage:
try:
    print(redirect_url("http://example.com/path"))
except Exception as e:
    print(e)

try:
    print(redirect_url("http://notexample.com/path"))
except Exception as e:
    print(e)