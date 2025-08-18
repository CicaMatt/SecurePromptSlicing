import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://example\.com/.*')

def get_redirect_url(target_url, default_url):
    # Use the compiled regular expression to match the target URL
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    target = "http://example.com/some/path"
    default = "https://default.com/"
    redirect_to = get_redirect_url(target, default)
    print(redirect_to)