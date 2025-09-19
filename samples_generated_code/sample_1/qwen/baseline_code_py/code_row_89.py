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
        'http://example.com/page1',
        'https://example.com/page2',
        'http://anotherdomain.com/page3',
        'ftp://example.com/page4'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")