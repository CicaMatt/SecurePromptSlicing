import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')
default_url = 'https://default.com'

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    match = url_pattern.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        return target_url
    else:
        # If the target URL does not match, use a default URL
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/redirect/somepath',
        'https://example.com/redirect/anotherpath',
        'http://wrongdomain.com/path',
        'ftp://example.com/redirect/path'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")