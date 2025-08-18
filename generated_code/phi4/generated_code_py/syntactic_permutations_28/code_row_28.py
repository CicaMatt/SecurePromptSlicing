import re

# Compile the regular expression once when the module loads
pattern = re.compile(r'^https://example\.com/somepath/.*$')

def get_redirect_url(target_url, default_url="https://default.com"):
    # Check if the target URL matches the pattern
    if pattern.match(target_url):
        return target_url  # Use as redirect target
    else:
        return default_url  # Use default URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/somepath/123",
        "https://example.com/otherpath/456",
        "http://example.com/somepath/789"
    ]

    for url in test_urls:
        print(f"Target URL: {url} -> Redirect URL: {get_redirect_url(url)}")