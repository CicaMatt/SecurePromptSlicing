import re

DEFAULT_URL = "http://default.url"
TARGET_PATTERN = r'^https?://(www\.)?example\.com(/.*)?$'
target_regex = re.compile(TARGET_PATTERN)

def get_redirect_url(url):
    if target_regex.match(url):
        return url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "https://www.example.com/path",
        "ftp://example.com",
        "http://anotherdomain.com"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")