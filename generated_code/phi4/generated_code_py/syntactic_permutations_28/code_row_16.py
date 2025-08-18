import re

# Compile the regular expression once when the module is loaded
regex = re.compile(r'https?://(?:www\.)?example\.com/.*')

def get_redirect_url(url):
    # Default URL if no match
    default_url = 'https://default.com/'

    # Check if the target URL matches the regex pattern
    if regex.match(url):
        return url  # Use as redirect target

    # If it does not match, use the default URL
    return default_url

# Example usage:
if __name__ == "__main__":
    test_urls = [
        "https://www.example.com/page1",
        "http://example.com/page2",
        "https://otherdomain.com/resource",
        "ftp://example.com/download"
    ]

    for url in test_urls:
        print(f"Original URL: {url} -> Redirect URL: {get_redirect_url(url)}")