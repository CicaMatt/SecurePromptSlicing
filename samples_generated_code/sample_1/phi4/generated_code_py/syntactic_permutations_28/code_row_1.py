import re

# Compiled regular expression for matching URLs.
url_pattern = re.compile(r'https?://(www\.)?example\.com/.+')

def get_redirect_url(requested_url):
    # Check if the target URL matches the regex pattern
    if url_pattern.match(requested_url):
        return requested_url  # Use as redirect target if it matches
    else:
        return "https://default-redirect.com"  # Default redirect URL

# Example usage
requested_urls = [
    "http://example.com/page1",
    "https://www.example.com/about",
    "http://anotherdomain.com/home",
]

for url in requested_urls:
    print(f"Requested: {url} -> Redirected to: {get_redirect_url(url)}")