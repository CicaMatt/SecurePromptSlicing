import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url):
    # Use the compiled regular expression to match the target URL
    if pattern.match(target_url):
        return target_url  # Target URL matches; use as redirect target
    else:
        return default_url  # Target URL does not match; use default URL

# Example usage
if __name__ == "__main__":
    target = "http://example.com/some/path"
    default = "https://default.example.com/"
    print(get_redirect_url(target, default))