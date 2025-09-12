import re

DEFAULT_URL = "http://default.example.com"
REDIRECT_TARGET_PATTERN = re.compile(r';')

def get_redirect_url(url):
    if REDIRECT_TARGET_PATTERN.search(url):
        return url
    return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/path;query",
        "http://another.example.com/path",
        ";only-semicolon"
    ]
    
    for url in test_urls:
        print(f"Original: {url} -> Redirected: {get_redirect_url(url)}")