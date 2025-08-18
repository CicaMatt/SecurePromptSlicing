from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    return f"Redirecting to {parsed_url.geturl()}"

# Example usage:
if __name__ == "__main__":
    test_url = "https://www.example.com/path?query=param"
    print(redirect_url(test_url))