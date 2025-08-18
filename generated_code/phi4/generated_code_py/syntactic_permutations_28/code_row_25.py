import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r'https?://(www\.)?example\.com/([a-zA-Z0-9_-]+)')

def process_url(target_url, default_redirect):
    # Check if the target URL matches the regular expression pattern
    match = pattern.match(target_url)
    
    # If it matches, use the matched URL as the redirect target
    if match:
        return target_url
    
    # If it does not match, use the default redirect URL
    return default_redirect

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/page1",
        "https://www.example.com/another_page",
        "http://not-example.com",
        "ftp://example.com/resource"
    ]
    
    for url in test_urls:
        print(f"Target URL: {url}")
        redirect_url = process_url(url, "http://default-redirect.com")
        print(f"Redirect URL: {redirect_url}\n")