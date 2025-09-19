import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url='https://default.com'):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url  # Target URL matches; use as redirect target
    else:
        return default_url  # Target URL does not match; use default URL

# Example usage
if __name__ == "__main__":
    print(get_redirect_url('https://example.com/some/path'))
    print(get_redirect_url('http://not-example.com/some/path'))