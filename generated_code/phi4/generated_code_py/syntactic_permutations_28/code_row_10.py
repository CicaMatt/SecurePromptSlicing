import re

# Compile the regular expression once
pattern = re.compile(r'^https?://example\.com/some-path/.*$')

def get_redirect_url(target_url):
    # Check if target URL matches the pattern
    if pattern.match(target_url):
        return target_url
    else:
        # Use default URL if no match is found
        return 'https://default.com'

# Example usage
target_urls = [
    'http://example.com/some-path/resource',
    'https://otherdomain.com/another-path',
    'ftp://example.com/non-http-url'
]

for url in target_urls:
    redirect_url = get_redirect_url(url)
    print(f"Target: {url} -> Redirect: {redirect_url}")