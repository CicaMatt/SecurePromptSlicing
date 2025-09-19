import re

# Compile the regular expression once when the module is loaded
target_url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='http://default.com'):
    # Check if the target URL matches the pattern
    if target_url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    print(get_redirect_url("http://example.com/some/path"))  # Should print: http://example.com/some/path
    print(get_redirect_url("http://otherdomain.com/path"))     # Should print: http://default.com