import re

# Compile the regular expression once when the module is loaded.
url_pattern = re.compile(r'https?://(?:www\.)?example\.com/.*')

def get_redirect_url(input_url, default_url='https://www.default.com'):
    # Check if input URL matches the compiled pattern
    if url_pattern.match(input_url):
        return input_url  # Use as redirect target if it matches
    else:
        return default_url  # Return default URL if no match

# Example usage:
if __name__ == "__main__":
    test_urls = [
        'http://www.example.com/page',
        'https://example.com/anotherpage',
        'http://test.com/somepage',
        'https://www.default.com'
    ]

    for url in test_urls:
        print(f"Input URL: {url} -> Redirect to: {get_redirect_url(url)}")