from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        return f"Redirected to {url}"
    else:
        return "404 Error: Not found"


To test this function, you can use:


# Test cases
print(redirect_url("http://www.example.com/path/to/resource"))
print(redirect_url("http://www.anotherdomain.com/path/to/resource"))