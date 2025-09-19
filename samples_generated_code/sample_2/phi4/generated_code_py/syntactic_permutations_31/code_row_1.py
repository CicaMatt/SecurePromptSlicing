from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        # Redirect logic here, for demonstration purposes we'll just return the URL
        return f"Redirecting to {url}"
    else:
        raise Exception("404 Not Found")

# Example usage:
try:
    print(redirect_url("http://example.com/somepath"))
except Exception as e:
    print(e)

try:
    print(redirect_url("http://anotherdomain.com/somepath"))
except Exception as e:
    print(e)