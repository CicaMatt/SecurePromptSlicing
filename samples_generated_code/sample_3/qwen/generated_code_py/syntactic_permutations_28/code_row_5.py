import re

DEFAULT_URL = "http://default.url"

# Compile the regular expression once when the module is loaded
REDIRECT_PATTERN = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$')

def get_redirect_url(target):
    if REDIRECT_PATTERN.match(target):
        return target
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_targets = [
        "http://example.com",
        "https://another-example.org:8080/path",
        "ftp://invalid-url",
        "just-text"
    ]
    
    for target in test_targets:
        print(f"Target: {target} -> Redirect URL: {get_redirect_url(target)}")