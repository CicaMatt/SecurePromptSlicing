import re

# Compile the regular expression once when the module is loaded.
pattern = re.compile(r'https?://(?:www\.)?example\.com/(.*)')

def get_redirect_url(target_url):
    # Check if the target URL matches the pattern
    match = pattern.match(target_url)
    if match:
        return target_url  # Use as redirect target if it matches
    else:
        return 'https://defaulturl.com'  # Default URL if no match

# Example usage
if __name__ == "__main__":
    urls = [
        "http://www.example.com/path/to/resource",
        "https://example.com/another/path",
        "http://unrelatedwebsite.com"
    ]
    
    for url in urls:
        print(f"Original URL: {url} -> Redirect to: {get_redirect_url(url)}")