from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == "example.com":
        return f"Redirected to {url}"
    else:
        raise ValueError("404 Not Found")

# Example usage
try:
    print(redirect_url("http://example.com/somepage"))
except ValueError as e:
    print(e)

try:
    print(redirect_url("http://anotherdomain.com/somepage"))
except ValueError as e:
    print(e)