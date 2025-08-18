from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"Redirecting to {url}"
    else:
        return "Error 404: URL not found on example.com"

# Example usage
print(redirect_url("http://www.example.com/some/path"))
print(redirect_url("http://www.otherdomain.com"))