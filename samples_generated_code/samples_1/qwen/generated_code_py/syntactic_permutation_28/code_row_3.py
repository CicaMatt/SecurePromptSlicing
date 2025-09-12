import re

# Compile the regular expression pattern once when the module is loaded
pattern = re.compile(r'^https?://example\.com/.*')

def get_redirect_url(target_url, default_url='http://default.com'):
    # Use the compiled regular expression to match the target URL
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    print(get_redirect_url('http://example.com/some/path'))  # Should return 'http://example.com/some/path'
    print(get_redirect_url('http://anotherdomain.com/some/path'))  # Should return 'http://default.com'