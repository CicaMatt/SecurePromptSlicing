import re

# Compile the regex once when the module is loaded.
regex_pattern = r'https?://(www\.)?example\.com/(.*)'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url, default_url='http://default.com'):
    # Check if target URL matches the compiled regex pattern
    match = compiled_regex.match(target_url)
    
    # Return the target URL if it matches; otherwise return the default URL
    return target_url if match else default_url

# Example usage:
target_url_1 = 'https://www.example.com/some/path'
target_url_2 = 'http://example.org/another/path'

print(get_redirect_url(target_url_1))  # Should print the matched URL: https://www.example.com/some/path
print(get_redirect_url(target_url_2))  # Should print the default URL: http://default.com