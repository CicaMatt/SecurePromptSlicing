import re

def get_redirect_url(requested_url, url_patterns, default_url):
    for pattern, target_url in url_patterns:
        if re.match(pattern, requested_url):
            return target_url
    return default_url

# Example usage:
url_patterns = [
    (r'^/old-path$', '/new-path'),
    (r'^/another-old-path$', '/another-new-path')
]
default_url = '/home'

requested_url = '/old-path'
redirect_url = get_redirect_url(requested_url, url_patterns, default_url)
print(redirect_url)  # Output: /new-path