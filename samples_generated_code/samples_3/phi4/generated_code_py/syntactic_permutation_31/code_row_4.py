from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    return f"Redirecting to scheme: {parsed_url.scheme}, netloc: {parsed_url.netloc}, path: {parsed_url.path}"

# Example usage:
if __name__ == "__main__":
    url_to_redirect = "https://www.example.com/path/to/resource?query=param"
    print(redirect_url(url_to_redirect))