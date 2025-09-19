import re

DEFAULT_URL = "http://default.url"

REDIRECT_PATTERN = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$')

def get_redirect_url(target):
    if REDIRECT_PATTERN.match(target):
        return target
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "https://another.example.org/path?query=123",
        "ftp://invalid.url",
        "justastring"
    ]
    
    for url in test_urls:
        print(f"Original: {url} -> Redirected: {get_redirect_url(url)}")