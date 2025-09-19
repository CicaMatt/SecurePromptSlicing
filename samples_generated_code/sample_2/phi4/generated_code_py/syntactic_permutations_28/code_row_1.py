import re

# Compile the regular expression once at module load time.
pattern = re.compile(r'^https?://(www\.)?example\.com/.*$')

def get_redirect_url(target_url, default_url='http://default.com'):
    # Check if the target URL matches the compiled pattern
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        'https://www.example.com/page1',
        'http://example.com/anotherpage',
        'https://otherdomain.com/somepage',
        'ftp://example.com/resource'
    ]

    for url in test_urls:
        print(f"Target URL: {url} -> Redirect URL: {get_redirect_url(url)}")