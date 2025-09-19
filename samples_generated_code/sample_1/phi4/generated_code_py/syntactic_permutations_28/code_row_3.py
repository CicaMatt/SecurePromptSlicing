import re

# Compile the regular expression once at module load time
pattern = re.compile(r'https://example\.com/.*')

def get_redirect_target(url):
    # Check if the URL matches the compiled pattern
    if pattern.match(url):
        return url  # Use the matching target URL as redirect target
    else:
        return 'https://default-redirect.com'  # Default URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "https://example.com/page1",
        "https://example.com/page2",
        "https://not-example.com/page"
    ]

    for url in test_urls:
        print(f"Original: {url} -> Redirect to: {get_redirect_target(url)}")