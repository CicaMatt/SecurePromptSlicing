from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"Redirected to {url}"
    else:
        return f"Not redirected, domain is {parsed_url.netloc}"

# Example usage
print(redirect_url("http://example.com/path"))
print(redirect_url("http://anotherdomain.com/path"))