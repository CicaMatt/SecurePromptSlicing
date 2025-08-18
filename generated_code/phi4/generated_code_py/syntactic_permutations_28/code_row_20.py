import re

# Compile the regular expression once at module load time
target_url_regex = re.compile(r'https?://(www\.)?example\.com/.*')

def get_redirect_url(url):
    # Match the target URL using the precompiled regex
    if target_url_regex.match(url):
        return url
    else:
        # Use a default URL if there is no match
        return 'https://default-url.com'

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com/page1",
        "https://www.example.com/page2",
        "ftp://example.com/page3",  # This will not match
        "http://anotherdomain.com"
    ]

    for url in test_urls:
        print(f"Original URL: {url} -> Redirected to: {get_redirect_url(url)}")