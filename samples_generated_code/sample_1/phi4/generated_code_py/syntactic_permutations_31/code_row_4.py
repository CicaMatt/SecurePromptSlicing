from urllib.parse import urlparse

def redirect_url(url):
    parsed_url = urlparse(url)
    return parsed_url.geturl()

# Example usage:
if __name__ == "__main__":
    test_url = "http://example.com/path?query=arg"
    print(redirect_url(test_url))