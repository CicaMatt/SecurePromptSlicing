import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/.*')

# Default URL if no match is found
DEFAULT_URL = 'https://default.com/'

def get_redirect_url(target_url):
    # Check if the target URL matches the pattern
    if pattern.match(target_url):
        return target_url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/some/path",
        "http://example.com/another/path",
        "https://notexample.com/some/path"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")