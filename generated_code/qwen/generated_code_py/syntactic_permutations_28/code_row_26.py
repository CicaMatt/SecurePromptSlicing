import re

# Compile the regular expression pattern once
pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='http://default.com'):
    # Check if the target URL matches the pattern
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/some/path",
        "http://example.com/another/path",
        "https://otherdomain.com/some/path"
    ]
    
    for url in test_urls:
        print(f"Original: {url} -> Redirected: {get_redirect_url(url)}")