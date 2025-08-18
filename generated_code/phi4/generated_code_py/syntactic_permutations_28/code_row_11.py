import re

# Compile the regular expression once at module level
pattern = re.compile(r'https?://example\.com/.*')

def get_redirect_url(target_url, default_url='https://default.com'):
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/page1",
        "https://example.com/page2",
        "http://other.com/page3"
    ]

    for url in test_urls:
        redirect_url = get_redirect_url(url)
        print(f"Original URL: {url} -> Redirected to: {redirect_url}")