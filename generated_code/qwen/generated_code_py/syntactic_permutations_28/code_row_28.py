import re

# Compile the regular expression pattern
pattern = re.compile(r'your_regex_pattern_here')

# Default URL to use if no match is found
default_url = 'http://default.example.com'

def get_redirect_url(target_url):
    # Check if the target URL matches the pattern
    if pattern.match(target_url):
        return target_url
    else:
        return default_url

# Example usage
if __name__ == "__main__":
    test_urls = [
        "http://example.com",
        "http://another.example.com",
        "http://notmatching.example.com"
    ]
    
    for url in test_urls:
        print(f"Original URL: {url} -> Redirected URL: {get_redirect_url(url)}")