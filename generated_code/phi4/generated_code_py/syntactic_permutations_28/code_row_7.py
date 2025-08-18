import re

def get_redirect_url(target_url, pattern, default_url):
    compiled_pattern = re.compile(pattern)
    
    if compiled_pattern.match(target_url):
        return target_url
    
    return default_url

# Example usage:
pattern = r'^https?://example\.com/.*$'
default_url = 'https://default.com/'
target_url = 'http://example.com/some/path'

redirect_url = get_redirect_url(target_url, pattern, default_url)
print(redirect_url)