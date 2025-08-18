import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'https?://example\.com/.*')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Use the compiled regular expression to match the target URL
    if pattern.match(target_url):
        # If the target URL matches; it is used as the redirect target
        return target_url
    else:
        # If the target URL does not match a default URL is used
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/page1',
        'https://example.com/page2',
        'http://not-example.com/page3'
    ]
    
    for url in test_urls:
        print(f"Original: {url} -> Redirect: {get_redirect_url(url)}")