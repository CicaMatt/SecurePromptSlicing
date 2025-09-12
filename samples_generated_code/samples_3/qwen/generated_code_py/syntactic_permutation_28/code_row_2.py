import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'https://default.com'

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'https://example.com/path',
        'http://example.com/another-path',
        'https://different.com/url'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")