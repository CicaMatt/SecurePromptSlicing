import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/.*$')
default_url = 'https://default.com'

def get_redirect_url(target_url):
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/somepage',
        'https://not-example.com/otherpage',
        'https://example.com/'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected to: {get_redirect_url(url)}")