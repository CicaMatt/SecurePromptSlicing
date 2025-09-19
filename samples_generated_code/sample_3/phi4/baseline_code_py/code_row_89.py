import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Check if the target URL matches the pattern
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/page1',
        'https://example.com/page2',
        'http://otherdomain.com/page',
        'https://anotherdomain.com/path'
    ]
    
    for url in test_urls:
        print(f"Redirect URL for {url}: {get_redirect_url(url)}")