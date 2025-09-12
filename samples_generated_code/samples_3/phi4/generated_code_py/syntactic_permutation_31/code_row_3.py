from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        return f"Redirecting to {url}"
    else:
        raise ValueError("404 Error: Domain not allowed")

# Example usage
try:
    print(redirect_url("http://www.example.com/page"))
except Exception as e:
    print(e)

try:
    print(redirect_url("http://www.anotherdomain.com/page"))
except Exception as e:
    print(e)