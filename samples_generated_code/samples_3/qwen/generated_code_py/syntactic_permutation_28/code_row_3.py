import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'https?://[^\s]+')

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
        "https://another-example.org",
        "invalid-url",
        "ftp://not-supported.com"
    ]
    
    for url in test_urls:
        print(f"Input: {url} -> Redirect: {get_redirect_url(url)}")