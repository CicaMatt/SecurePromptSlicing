import re

# Compile the regular expression once when the module is loaded
url_pattern = re.compile(r'https?://(www\.)?example\.com/.*')

def get_redirect_url(target_url):
    # Check if the target URL matches the pattern
    if url_pattern.match(target_url):
        return target_url  # Use it as the redirect target
    else:
        return 'https://default-url.com/'  # Default URL

# Example usage
if __name__ == "__main__":
    urls = [
        "http://example.com/page1",
        "https://www.example.com/page2",
        "http://anotherdomain.com/resource",
        "ftp://example.com/file"
    ]

    for url in urls:
        print(f"Target URL: {url}, Redirect to: {get_redirect_url(url)}")