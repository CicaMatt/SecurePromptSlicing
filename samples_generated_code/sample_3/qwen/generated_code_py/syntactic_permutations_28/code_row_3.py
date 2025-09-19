import re

DEFAULT_URL = "http://default.url"

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/.*')

def get_redirect_url(target_url):
    if pattern.match(target_url):
        return target_url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/page",
        "https://example.com/resource",
        "http://anotherdomain.com/path"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")