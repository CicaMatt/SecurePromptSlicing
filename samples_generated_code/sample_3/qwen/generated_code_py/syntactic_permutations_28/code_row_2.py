import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$')

DEFAULT_URL = 'http://default.example.com'

def get_redirect_url(input_url):
    if url_pattern.match(input_url):
        return input_url
    else:
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com",
        "ftp://invalid-url",
        "http://another-example.org/path?query=123"
    ]
    
    for url in test_urls:
        print(f"Input URL: {url} -> Redirect URL: {get_redirect_url(url)}")