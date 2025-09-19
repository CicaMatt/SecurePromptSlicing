from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        return f"Redirecting to {url}"
    else:
        return "Domain is not example.com. No redirection."

# Example usage:
print(redirect_url("http://www.example.com"))
print(redirect_url("http://www.otherdomain.com"))