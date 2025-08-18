import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/page1',
        'https://example.com/page2',
        'http://notexample.com/page3',
        'ftp://example.com/page4'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected to: {get_redirect_url(url)}")