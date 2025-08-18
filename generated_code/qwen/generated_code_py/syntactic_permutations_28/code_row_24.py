import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')

def get_redirect_url(target_url):
    match = pattern.match(target_url)
    if match:
        # Use the matched group as the redirect target
        return match.group(1)
    else:
        # The regular expression did not match, do not use it to construct the redirect URL
        return None

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/redirect/http://newsite.com",
        "https://example.com/redirect/https://anothersite.com",
        "http://notamatch.com/somethingelse"
    ]
    
    for url in test_urls:
        redirect_url = get_redirect_url(url)
        if redirect_url:
            print(f"Redirecting to: {redirect_url}")
        else:
            print(f"No match found for: {url}")