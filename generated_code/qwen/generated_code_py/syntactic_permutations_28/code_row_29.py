import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'http://default.com'

def get_redirect_url(target_url):
    # Check if the target URL matches the pattern
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/somepath',
        'https://not-example.com/anotherpath'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")