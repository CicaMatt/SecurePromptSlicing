import re

def get_redirect_url(target_url):
    # Define the compiled regex pattern for matching URLs.
    url_pattern = re.compile(r'https?://example\.com/somepath/.*')

    # Default redirect URL if no match is found.
    default_url = 'https://default.com'

    # Check if target URL matches the predefined pattern.
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage:
if __name__ == "__main__":
    test_urls = [
        "https://example.com/somepath/test",
        "http://example.com/anotherpath",
        "https://otherdomain.com/path"
    ]

    for url in test_urls:
        print(f"Redirecting {url} to {get_redirect_url(url)}")