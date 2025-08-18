import re

# Compile the regex pattern once when the module is loaded
pattern = re.compile(r'https?://(?:www\.)?example\.com/.*')

def get_redirect_target(url):
    # Use the compiled regex to match the target URL
    if pattern.match(url):
        return url  # Return the original URL as the redirect target
    return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://www.example.com/page1",
        "https://example.com/page2",
        "http://anotherdomain.com/page",
        "https://www.example.com/",
    ]

    for url in test_urls:
        redirect_target = get_redirect_target(url)
        if redirect_target:
            print(f"Redirect to: {redirect_target}")
        else:
            print(f"No redirect for: {url}")