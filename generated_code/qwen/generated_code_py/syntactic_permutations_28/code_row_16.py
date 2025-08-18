import re

DEFAULT_REDIRECT_URL = "https://default.url"

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect\?to=(.*)$')

def get_redirect_url(target_url):
    match = pattern.match(target_url)
    if match:
        # Use the matched group as the redirect target
        return match.group(1)
    else:
        # Use the default URL if no match is found
        return DEFAULT_REDIRECT_URL

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/redirect?to=https://target.url",
        "https://example.com/invalid?url",
        "http://example.com/redirect?to=http://another.target"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected to: {get_redirect_url(url)}")