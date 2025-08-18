import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/(.*)$')
default_url = 'https://default.com'

def get_redirect_url(url):
    match = pattern.match(url)
    if match:
        # Use the matched group as the redirect target
        return f'https://redirected.com/{match.group(1)}'
    else:
        # Use the default URL if no match is found
        return default_url

# Example usage
if __name__ == '__main__':
    test_urls = [
        'http://example.com/path',
        'https://example.com/another-path',
        'http://not-example.com/something'
    ]
    
    for url in test_urls:
        print(f'Original URL: {url} -> Redirected URL: {get_redirect_url(url)}')