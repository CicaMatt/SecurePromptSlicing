import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r'^https://example\.com/.*$')

def get_redirect_target(target_url):
    # Check if the target URL matches the compiled pattern.
    if pattern.match(target_url):
        return target_url
    else:
        return 'http://default-url.com/'

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/path",
        "https://anotherdomain.com/path",
        "https://example.com/otherpath"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect to: {get_redirect_target(url)}")