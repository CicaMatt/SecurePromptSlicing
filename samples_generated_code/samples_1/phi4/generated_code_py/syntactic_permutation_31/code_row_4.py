from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    return f"Redirecting to {parsed_url.geturl()}"

# Example usage:
print(redirect_url("https://www.example.com/path?query=1"))