import re

# Precompiled regex pattern for matching URLs
URL_PATTERN = re.compile(r'^https?://example\.com/.*$')
DEFAULT_URL = 'https://default.com'

def get_redirect_url(target_url):
    if URL_PATTERN.match(target_url):
        return target_url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/page1",
        "https://example.com/page2",
        "http://otherdomain.com/page3"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")