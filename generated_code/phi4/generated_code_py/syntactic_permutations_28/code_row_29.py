import re

def get_redirect_url(target_url, default_url):
    compiled_regex = re.compile(r'your-regex-pattern-here')  # Replace with your actual pattern
    if compiled_regex.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
target_url = "http://example.com/some-path"
default_url = "http://example.com/default-path"

redirect_url = get_redirect_url(target_url, default_url)
print(redirect_url)