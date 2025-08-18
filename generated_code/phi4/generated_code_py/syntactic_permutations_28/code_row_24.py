import re

# Compile the regular expression once
regex_pattern = r'^https?://example\.com/.*$'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url):
    # Check if target URL matches the compiled regex pattern
    if compiled_regex.match(target_url):
        return target_url  # Use as redirect target
    else:
        return 'http://default-redirect.com'  # Default redirect URL

# Example usage
target_url = 'https://example.com/page'
redirect_url = get_redirect_url(target_url)
print(redirect_url)  # Output: https://example.com/page

target_url = 'https://anotherdomain.com/page'
redirect_url = get_redirect_url(target_url)
print(redirect_url)  # Output: http://default-redirect.com