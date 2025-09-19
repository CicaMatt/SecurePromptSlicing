import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'https?://[^\s]+')

# Default URL if no match is found
DEFAULT_URL = 'https://example.com'

def get_redirect_url(input_string):
    # Check if the input string matches the URL pattern
    match = url_pattern.match(input_string)
    if match:
        # Use the matched URL as the redirect target
        return match.group(0)
    else:
        # Use the default URL
        return DEFAULT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "https://another-example.org/path",
        "not a url",
        "ftp://invalid-protocol.com"
    ]
    
    for url in test_urls:
        print(f"Input: {url} -> Redirect to: {get_redirect_url(url)}")