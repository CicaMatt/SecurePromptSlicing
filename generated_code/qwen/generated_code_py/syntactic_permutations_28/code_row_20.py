import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_target_url(target_url):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url
    else:
        # If the target URL does not match, use a default URL
        return 'https://default.com'

# Example usage
target = 'http://example.com/some/path'
redirect_url = get_target_url(target)
print(redirect_url)