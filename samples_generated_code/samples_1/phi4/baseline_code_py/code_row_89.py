import re

# Compile the regex once when the module is loaded.
pattern = re.compile(r'/some-pattern/')

def get_redirect_url(target_url, default_url='https://default.example.com'):
    # Use the compiled pattern to match against the target URL.
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage:
if __name__ == "__main__":
    test_urls = [
        '/some-pattern/resource1',
        '/other-pattern/resource2',
        '/some-pattern/resource3'
    ]

    for url in test_urls:
        print(f"Redirect URL for '{url}': {get_redirect_url(url)}")