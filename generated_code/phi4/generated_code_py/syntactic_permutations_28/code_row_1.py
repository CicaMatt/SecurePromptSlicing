import re

# Compile the regex once when module is loaded
regex_pattern = r'your-regex-pattern-here'
compiled_regex = re.compile(regex_pattern)

def get_redirect_url(target_url, default_url):
    # Check if target_url matches the compiled regex
    if compiled_regex.match(target_url):
        return target_url  # Use as redirect target if it matches
    else:
        return default_url  # Use default URL if no match

# Example usage
target_url = 'example.com/some-path'
default_url = 'https://default-redirect-url.com'

redirect_url = get_redirect_url(target_url, default_url)
print(redirect_url)