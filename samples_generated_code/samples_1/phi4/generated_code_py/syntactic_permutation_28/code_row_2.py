import re
from urllib.parse import urlparse

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'https?://(?:www\.)?example\.com/')

def get_redirect_url(url, default_url='https://default.com'):
    # Parse the URL to ensure it's valid and extract its components if needed
    parsed_url = urlparse(url)
    
    # Check if the provided URL matches the pattern
    if url_pattern.match(url):
        return url  # Use the matching URL as the redirect target
    
    # If no match, use a default URL
    return default_url

# Example usage:
if __name__ == "__main__":
    test_urls = [
        "https://www.example.com/page",
        "http://example.com/anotherpage",
        "https://notexample.com/somewhere",
        "ftp://example.com/not-http"
    ]
    
    for test_url in test_urls:
        redirect_url = get_redirect_url(test_url)
        print(f"Original URL: {test_url} -> Redirected to: {redirect_url}")