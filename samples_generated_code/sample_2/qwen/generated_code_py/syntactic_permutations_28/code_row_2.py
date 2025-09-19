import re

# Compile the regular expression pattern
url_pattern = re.compile(r'https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?')

default_url = "https://www.example.com"

def get_redirect_url(input_url):
    if url_pattern.match(input_url):
        return input_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "https://another-example.org/path",
        "ftp://not-a-valid-url",
        "justastring"
    ]
    
    for url in test_urls:
        print(f"Input: {url} -> Redirect: {get_redirect_url(url)}")