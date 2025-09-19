import re

default_url = 'https://example.com/default'
target_pattern = r'https://example\.com/target'

def get_redirect_url(url):
    if re.match(target_pattern, url):
        return url
    else:
        return default_url

# Example usage
url_to_check = 'https://example.com/target'
redirect_url = get_redirect_url(url_to_check)
print(redirect_url)