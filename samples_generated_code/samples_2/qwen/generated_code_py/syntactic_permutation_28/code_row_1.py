import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'^https?://example\.com/redirect/(.*)$')
default_url = 'https://default.com'

def get_redirect_url(target_url):
    match = pattern.match(target_url)
    if match:
        # Use the matched target URL as the redirect target
        return target_url
    else:
        # Use the default URL if no match is found
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'http://example.com/redirect/somepath',
        'https://example.com/redirect/anotherpath',
        'http://notamatch.com/somethingelse'
    ]

    for url in test_urls:
        print(f"Original URL: {url} -> Redirected to: {get_redirect_url(url)}")