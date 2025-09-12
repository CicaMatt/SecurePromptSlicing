import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?')

default_url = 'https://www.example.com'

def get_redirect_url(url):
    if url_pattern.match(url):
        return url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "https://another-example.org/path?query=123",
        "ftp://not-valid-url",
        "just-a-string"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")