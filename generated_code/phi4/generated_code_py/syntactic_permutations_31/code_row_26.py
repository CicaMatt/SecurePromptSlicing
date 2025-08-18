from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"Redirecting to {url}"
    else:
        return "404 Error: URL not found"

# Example usage:
print(redirect_url("http://www.example.com/page"))
print(redirect_url("http://www.otherdomain.com/page"))