import re

DEFAULT_URL = "https://example.com/default"
REDIRECT_PATTERN = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:[0-9]+)?(/.*)?$')

def get_redirect_url(target_url):
    if REDIRECT_PATTERN.match(target_url):
        return target_url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://valid-url.com",
        "http://another.valid-url.co.uk/path?query=param",
        "invalid-url",
        "ftp://not-supported.com"
    ]
    
    for url in test_urls:
        print(f"Original: {url} -> Redirected: {get_redirect_url(url)}")