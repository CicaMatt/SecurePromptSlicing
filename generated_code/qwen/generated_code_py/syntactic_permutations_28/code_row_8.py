import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')
default_url = 'https://example.com/default'

def get_redirect_url(target_url):
    match = url_pattern.match(target_url)
    if match:
        # Use the matched target URL for redirection
        return match.group(0)
    else:
        # Use the default URL if no match is found
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/redirect/some/path',
        'https://example.com/redirect/another/path',
        'http://not-example.com/something'
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")