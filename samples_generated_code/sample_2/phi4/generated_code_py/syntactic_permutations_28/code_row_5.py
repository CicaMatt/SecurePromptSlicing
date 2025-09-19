import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r'your-regex-pattern-here')

def get_redirect_url(target_url, default_url):
    # Check if the target URL matches the compiled regex pattern.
    match = pattern.match(target_url)
    
    # Use the target URL if it matches; otherwise, use the default URL.
    if match:
        return target_url
    else:
        return default_url

# Example usage:
target_url = "example-target-url"
default_url = "https://default-url.com"

redirected_url = get_redirect_url(target_url, default_url)
print(redirected_url)