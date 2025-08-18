import re

# Compile the regular expression when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def get_redirect_url(target_url, default_url):
    # Use the compiled regular expression to match the target URL
    match = url_pattern.match(target_url)
    if match:
        # If the target URL matches, use it as the redirect target
        return target_url
    else:
        # If the target URL does not match, use a default URL
        return default_url

# Example usage
if __name__ == "__main__":
    test_url = "http://example.com/redirect/some/path"
    default_redirect = "https://default.example.com"
    print(get_redirect_url(test_url, default_redirect))