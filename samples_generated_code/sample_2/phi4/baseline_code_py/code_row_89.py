import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'https?://(?:www\.)?example\.com/.*')

def get_redirect_url(target_url, default_url='https://default-url.com'):
    # Check if the target URL matches the compiled pattern
    if url_pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://www.example.com/some/path",
        "https://example.com/another/path",
        "http://not-example.com/no-match",
    ]

    for url in test_urls:
        print(f"Target URL: {url} -> Redirect URL: {get_redirect_url(url)}")