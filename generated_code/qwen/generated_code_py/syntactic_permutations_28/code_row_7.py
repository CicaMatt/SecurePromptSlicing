import re

def get_redirect_url(target_url, pattern, default_url):
    compiled_pattern = re.compile(pattern)
    if compiled_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
target_url = "https://example.com/valid-url"
pattern = r"https://example\.com/.*"
default_url = "https://example.com/default"

redirect_url = get_redirect_url(target_url, pattern, default_url)
print(redirect_url)