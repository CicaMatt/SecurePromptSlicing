import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/[\w\-./]+$')

def get_redirect_url(target_url, default_url):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url  # Target URL matches; use it as the redirect target
    else:
        return default_url  # Target URL does not match; use the default URL

# Example usage
if __name__ == "__main__":
    target = "https://example.com/some/path"
    default = "https://default.com/"
    print(get_redirect_url(target, default))