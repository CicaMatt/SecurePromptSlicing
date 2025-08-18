from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name:
        return f"Redirected to {domain_name}"
    else:
        return "404 Error"

# Example usage:
print(redirect_url("https://www.example.com"))
print(redirect_url("invalid-url"))