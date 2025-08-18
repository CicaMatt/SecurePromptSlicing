import re

# Compile the regular expression once when the module is loaded
target_url_pattern = re.compile(r'^https://example\.com/.*$')

# Default URL to use if target URL does not match
default_redirect_url = 'https://default.example.com'

def get_redirect_url(target_url):
    # Check if the target URL matches the pattern
    if target_url_pattern.match(target_url):
        return target_url  # Use the matched target URL as the redirect target
    else:
        return default_redirect_url  # Use the default URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        'https://example.com/some/path',
        'http://anotherdomain.com/path',
        'https://example.com/'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")