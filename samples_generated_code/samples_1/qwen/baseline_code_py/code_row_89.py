import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')
default_url = 'https://example.com/default'

def get_redirect_url(target_url):
    match = pattern.match(target_url)
    if match:
        # Use the target URL as the redirect target
        return target_url
    else:
        # Use the default URL
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'https://example.com/redirect/somepath',
        'http://example.com/redirect/anotherpath',
        'https://differentdomain.com/path'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")