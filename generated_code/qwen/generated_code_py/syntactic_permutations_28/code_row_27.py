import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*$')

def get_redirect_url(target_url, default_url):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url
    else:
        return None  # or return default_url if you want to use it when there's no match

# Example usage
if __name__ == "__main__":
    test_target_url = "https://example.com/some/path"
    default_url = "https://default.com"
    
    redirect_url = get_redirect_url(test_target_url, default_url)
    print(redirect_url)  # Output: https://example.com/some/path