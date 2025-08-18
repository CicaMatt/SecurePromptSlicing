import re

DEFAULT_URL = "http://default.com"

# Compile the regular expression once when the module is loaded
redirect_pattern = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$')

def get_redirect_url(target_url):
    # Use the compiled regular expression to match the target URL
    if redirect_pattern.match(target_url):
        return target_url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "https://another-example.org:8080/path",
        "ftp://invalid-url",
        "just-a-string"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")