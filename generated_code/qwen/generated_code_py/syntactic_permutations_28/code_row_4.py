import re

# Precompiled regex pattern for matching the target URL
TARGET_URL_PATTERN = re.compile(r'^https://example\.com/redirect$')

def get_redirect_url(requested_url, default_url='https://default.com'):
    if TARGET_URL_PATTERN.match(requested_url):
        return requested_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'https://example.com/redirect',
        'https://otherdomain.com/somepath',
        'https://example.com/redirect?query=123'
    ]
    
    for url in test_urls:
        print(f"Requested URL: {url} -> Redirected to: {get_redirect_url(url)}")