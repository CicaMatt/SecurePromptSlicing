import re

# Compile the regular expression once when loaded.
regex = re.compile(r'your-regex-pattern')

def get_redirect_url(target_url, default_url):
    # Check if the target URL matches the compiled regex pattern.
    if regex.match(target_url):
        return target_url  # Use the target URL as the redirect target.
    else:
        return default_url  # Use a default URL if there is no match.

# Example usage
target_url = "http://example.com/some-path"
default_url = "http://example.com/default"

redirect_url = get_redirect_url(target_url, default_url)
print(redirect_url)